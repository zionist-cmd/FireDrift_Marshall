#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Лог платы карта по USB: всё, что D1 mini печатает в порт, с метками времени.

    py usb_log.py                 найти CH340 сам, писать в logs/usb/
    py usb_log.py --kart 12       имя карта в имени файла
    py usb_log.py --port COM5
    py usb_log.py --rom-port COM7 второй переходник на TX платы: причина сброса

Прошивка печатает на 115200: обрывы вебсокета ([WSc] Disconnected), команды
сервера, этапы загрузки (Start FS, Start WIFI ...) и, если программа упала,
отчёт ядра (Exception, Soft WDT). Причину сброса ROM печатает на 74880 — на
115200 она приходит мусором, его пишем как признак перезагрузки. Разобрать
причину из мусора надёжно нельзя (проверено 25.11: отрыв в один бит), поэтому
для неё второй USB-TTL переходник: RX переходника — на TX платы, GND — на G.
Он слушает на 74880 и пишет «rst cause» текстом.

Плата при загрузке печатает свой config.json с паролем Wi-Fi — logs/ в git не
попадает, но лог не пересылать.

Порт открывается без дёрганья DTR/RTS: иначе D1 mini перезагрузится.
Нужен pyserial (ставится вместе с esptool).
"""

import argparse
import os
import re
import sys
import threading
import time

import serial
import serial.tools.list_ports

CH340_VID = 0x1A86
ROM_BAUD = 74880
# Причины сброса из загрузчика ESP8266 (rst cause:N).
RST_CAUSE = {1: "включение или провал питания", 2: "ножка RST (кнопка, помеха) или "
             "программный перезапуск", 4: "аппаратный сторожевой таймер — программа зависла"}
TAGS = (
    ("[WSc] Disconnected", "ОБРЫВ"),
    ("[WSc] Connected", "СВЯЗЬ"),
    ("Start FS", "ЗАГРУЗКА"),
    ("Exception", "СБОЙ"),
    ("Soft WDT", "СБОЙ"),
    ("wdt reset", "СБОЙ"),
    (">>>stack>>>", "СБОЙ"),
    ("rst cause", "СБРОС"),
    # Отладка прошивки (разбор 25.11). «ожидания» раньше «катания»: в строке
    # «закончилось время ожидания катания» есть оба слова.
    ("время ожидания", "ТАЙМАУТ 600 С"),
    ("локальн", "МЕСТНЫЙ РЕЖИМ"),
    ("время парковки", "ПАРКОВКА"),
    ("время катания", "КАТАНИЕ"),
    ("Связь отсутствует", "12 Ч БЕЗ СВЯЗИ"),
)


def find_port(skip=None):
    for p in serial.tools.list_ports.comports():
        if p.vid == CH340_VID and p.device != skip:
            return p.device
    return None


def rom_line(raw):
    """Строка с второго переходника (74880): только причина сброса, прочее — мусор."""
    text = raw.decode("ascii", "replace").strip()
    m = re.search(r"rst cause:(\d+)", text)
    if not m:
        return None
    cause = int(m.group(1))
    return "%s — %s" % (text, RST_CAUSE.get(cause, "другая (%d)" % cause)), "ПРИЧИНА"


def tag(line):
    for needle, name in TAGS:
        if needle in line:
            return name
    return ""


def decode(raw):
    """Строка платы или пометка о мусоре (загрузка ROM на 74880).

    Сообщения производителя — по-русски, в UTF-8. Их читаем как текст: 25.11
    «закончилось время ожидания катания» записалось как перезагрузка.
    """
    try:
        text = raw.decode("utf-8").rstrip("\r\n")
    except UnicodeDecodeError:
        text = raw.decode("ascii", "replace").rstrip("\r\n")
    bad = text.count("�") + sum(1 for c in text if ord(c) < 32 and c != "\t")
    if text and bad * 3 > len(text):
        return "[мусор %d байт — плата перезагрузилась (ROM на 74880)]" % len(raw), "ПЕРЕЗАГРУЗКА"
    return text, tag(text)


class Log(object):
    def __init__(self, out_dir, kart):
        self.out_dir, self.kart = out_dir, kart
        self.lock = threading.Lock()
        os.makedirs(out_dir, exist_ok=True)

    def write(self, text, label=""):
        now = time.time()
        stamp = time.strftime("%H:%M:%S", time.localtime(now)) + ".%03d" % (now % 1 * 1000)
        line = "%s  %-12s %s" % (stamp, "[%s]" % label if label else "", text)
        name = "%s-%s.log" % (self.kart, time.strftime("%Y-%m-%d"))
        with self.lock:
            print(line, flush=True)
            with open(os.path.join(self.out_dir, name), "a", encoding="utf-8") as fh:
                fh.write(line + "\n")


def keep_awake():
    """Пока пишем лог, Windows не засыпает; экран гаснуть может.

    Настройки питания не меняются: просьба живёт, пока жив этот процесс.
    Закрытая крышка ноутбука всё равно усыпит его.
    """
    if sys.platform == "win32":
        import ctypes
        es_continuous, es_system_required = 0x80000000, 0x00000001
        ctypes.windll.kernel32.SetThreadExecutionState(es_continuous | es_system_required)


def open_port(port, baud):
    ser = serial.Serial()
    ser.port, ser.baudrate, ser.timeout = port, baud, 0.5
    ser.dtr = False               # DTR/RTS на D1 mini — это сброс и режим прошивки
    ser.rts = False
    ser.open()
    return ser


def run(pick_port, baud, log, handle):
    """Читать порт строками; пропал — ждать и открыть снова."""
    while True:
        port = pick_port()
        if not port:
            time.sleep(1)
            continue
        try:
            ser = open_port(port, baud)
        except serial.SerialException:
            time.sleep(1)
            continue
        log.write("порт %s открыт, %d бод" % (port, baud), "USB")
        buf = b""
        try:
            while True:
                chunk = ser.read(256)
                if not chunk:
                    if buf:               # хвост без перевода строки
                        handle(buf)
                        buf = b""
                    continue
                buf += chunk
                while b"\n" in buf:
                    raw, buf = buf.split(b"\n", 1)
                    if raw.strip():
                        handle(raw)
        except (serial.SerialException, OSError) as e:
            # С заклеенным питанием USB порт живёт от платы: пропал вместе
            # с ней — значит, у платы пропадало питание.
            log.write("порт %s пропал: %s" % (port, e), "USB")
            ser.close()
            time.sleep(1)


def main():
    ap = argparse.ArgumentParser(description="Лог платы карта по USB")
    ap.add_argument("--port", help="COM-порт; по умолчанию первый CH340")
    ap.add_argument("--baud", type=int, default=115200)
    ap.add_argument("--rom-port", help="второй переходник на TX платы, 74880: причина сброса")
    ap.add_argument("--kart", default="kart", help="номер карта для имени файла")
    ap.add_argument("--out", default=os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                                  "logs", "usb"))
    args = ap.parse_args()
    log = Log(args.out, args.kart)
    keep_awake()
    log.write("жду плату по USB (CH340)%s; ноутбук не уснёт, пока идёт лог"
              % (", порт " + args.port if args.port else ""), "USB")
    if args.rom_port:
        def on_rom(raw):
            found = rom_line(raw)
            if found:
                log.write(*found)
        threading.Thread(target=run, daemon=True,
                         args=(lambda: args.rom_port, ROM_BAUD, log, on_rom)).start()
    try:
        run(lambda: args.port or find_port(skip=args.rom_port), args.baud, log,
            lambda raw: log.write(*decode(raw)))
    except KeyboardInterrupt:
        log.write("остановлено", "USB")
        sys.exit(0)


if __name__ == "__main__":
    main()
