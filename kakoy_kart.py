#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Какой это карт: читает DUUID с D1 mini по USB и показывает номер на кузове.

DUUID — номер чипа ESP8266, он же последние три байта MAC. Прошивка у всех
картов одна, различает их только он. Номер на кузове берётся из karts.conf —
того же, по которому сервер подписывает карты в панели.

Запуск — двойной щелчок по «Какой карт.bat». Скрипт ждёт платы: воткнули
кабель — показал номер, вынули — ждёт следующую. Или из консоли:

    py kakoy_kart.py                       ждать платы одну за другой
    py kakoy_kart.py --port COM5           прочитать одну и выйти
    py kakoy_kart.py --conf D:\\karts.conf  номера из другого файла

При чтении D1 mini перезагружается: карт на заезде не подключать.

Нужен esptool 5 (py -m pip install esptool), вместе с ним ставится pyserial.
"""

import argparse
import datetime
import importlib.util
import os
import re
import subprocess
import sys
import time

if not importlib.util.find_spec("esptool"):
    sys.exit("  Нужен esptool: py -m pip install esptool")

from serial.tools import list_ports

HERE = os.path.dirname(os.path.abspath(__file__))

# USB-переходники на D1 mini: CH340, на некоторых клонах CP2102.
# Блютуз-порты ноутбука (COM3, COM4) сюда не попадают.
USB_VIDS = (0x1A86, 0x10C4)


def read_names(path):
    """karts.conf: `<DUUID> = номер`. Строки `.speed` и `.crawl` пропускаем."""
    names = {}
    with open(path, encoding="utf-8") as fh:
        for line in fh:
            line = line.split("#", 1)[0].strip()
            if "=" not in line:
                continue
            key, val = (s.strip() for s in line.split("=", 1))
            if key.isdigit():
                names[key] = val
    return names


def usb_ports():
    return {p.device for p in list_ports.comports() if p.vid in USB_VIDS}


def read_chip(port):
    """MAC и DUUID через esptool. Chip ID у ESP8266 и есть DUUID прошивки."""
    run = subprocess.run(
        [sys.executable, "-m", "esptool", "--port", port, "--no-stub", "chip-id"],
        capture_output=True, text=True, errors="replace")
    out = run.stdout + run.stderr
    chip = re.search(r"Chip ID:\s*0x([0-9a-fA-F]+)", out)
    if not chip:
        fatal = re.search(r"A fatal error occurred:\s*(.+)", out)
        lines = out.strip().splitlines()
        raise RuntimeError(fatal.group(1).strip() if fatal else
                           lines[-1] if lines else "esptool ничего не ответил")
    mac = re.search(r"MAC:\s*((?:[0-9a-fA-F]{2}:){5}[0-9a-fA-F]{2})", out)
    return (mac.group(1).lower() if mac else "?"), int(chip.group(1), 16)


def show(port, names):
    # Пока грузится прошивка, порт может пропасть на доли секунды — пробуем ещё.
    for tries in (1, 2, 3):
        try:
            mac, duuid = read_chip(port)
            break
        except RuntimeError as e:
            if tries == 3:
                print("\n  %s: не прочитал — %s" % (port, e))
                print("  Закройте программы, которые держат порт, и воткните кабель заново.")
                return
            time.sleep(2)
    print("\n  %s   MAC %s   DUUID %d" % (port, mac, duuid))
    number = names.get(str(duuid))
    if number:
        print("  " + "=" * 28)
        print("        ЭТО КАРТ №%s" % number)
        print("  " + "=" * 28)
    elif names:
        print("  Этого DUUID в karts.conf нет: новый или запасной модуль.")
        print("  Номер на кузове ему вписывают в админке.")


def main():
    ap = argparse.ArgumentParser(description="Какой это карт — по DUUID с D1 mini.")
    ap.add_argument("--port", help="COM-порт; без него скрипт сам ждёт платы")
    ap.add_argument("--conf", default=os.path.join(HERE, "karts.conf"),
                    help="файл с номерами на кузове, по умолчанию karts.conf рядом")
    args = ap.parse_args()

    try:
        names = read_names(args.conf)
        day = datetime.date.fromtimestamp(os.path.getmtime(args.conf))
        print("  Номера из %s от %s, картов: %d."
              % (args.conf, day.strftime("%d.%m.%Y"), len(names)))
    except OSError:
        names = {}
        print("  Нет %s — покажу только DUUID." % args.conf)

    if args.port:
        show(args.port, names)
        return

    print("  Втыкайте D1 mini в USB. Выход — Ctrl+C.")
    done = {}                                # порт -> когда видели последний раз
    try:
        while True:
            now = time.time()
            ports = usb_ports()
            for port in ports & done.keys():
                done[port] = now
            # После перезагрузки ESP порт несколько раз пропадает на доли
            # секунды. Вынутой считаем плату, которой нет дольше 2 с.
            for port in [p for p in done if p not in ports and now - done[p] > 2]:
                del done[port]
                print("  Вынули. Жду следующую плату.")
            for port in sorted(ports - done.keys()):
                time.sleep(1)                # Windows не сразу отдаёт новый порт
                show(port, names)
                print("  Можно вынимать.")
                done[port] = time.time()
            time.sleep(0.3)
    except KeyboardInterrupt:
        pass


if __name__ == "__main__":
    main()
