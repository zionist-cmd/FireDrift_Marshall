#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Поддельный карт для проверки сервера и панелей без железа.

Изображает прошивку 0.9.10: подключается вебсокетом, представляется по Init,
отвечает на Status телеметрией, выполняет Start / Stop / MaxSpeed
и — как настоящая плата — сам гасит driveOn по истечении Length.

Запуск (в отдельном окне, рядом должен работать marshal.py):

    python fakekart.py                  три карта на localhost:8080
    python fakekart.py --karts 6        шесть картов
    python fakekart.py --host 10.20.0.50 --karts 4
    python fakekart.py --pedal          имитировать нажатую педаль

DUUID выдаются из диапазона 90000001+, чтобы не путать с настоящими.
Остановить — Ctrl+C.

Нужен только Python 3.7+, никаких pip-пакетов.
"""

import argparse
import base64
import json
import os
import random
import socket
import struct
import sys
import threading
import time


# ------------------------------------------------------------------ вебсокет

def ws_connect(host, port):
    s = socket.create_connection((host, port), 10)
    key = base64.b64encode(os.urandom(16)).decode()
    s.sendall((
        "GET / HTTP/1.1\r\n"
        "Host: %s:%d\r\n"
        "Upgrade: websocket\r\n"
        "Connection: Upgrade\r\n"
        "Sec-WebSocket-Key: %s\r\n"
        "Sec-WebSocket-Version: 13\r\n\r\n" % (host, port, key)
    ).encode())
    head = b""
    while b"\r\n\r\n" not in head:
        chunk = s.recv(1)
        if not chunk:
            raise OSError("сервер закрыл соединение при рукопожатии")
        head += chunk
    if b" 101 " not in head.split(b"\r\n")[0]:
        raise OSError("сервер не согласился на вебсокет: %s"
                      % head.split(b"\r\n")[0].decode("latin-1"))
    return s


def ws_send(sock, text):
    data = text.encode("utf-8")
    mask = os.urandom(4)
    head = bytearray([0x81])
    n = len(data)
    if n < 126:
        head.append(0x80 | n)
    elif n < 65536:
        head.append(0x80 | 126)
        head += struct.pack(">H", n)
    else:
        head.append(0x80 | 127)
        head += struct.pack(">Q", n)
    head += mask
    sock.sendall(bytes(head) + bytes(c ^ mask[i % 4] for i, c in enumerate(data)))


def ws_recv(sock):
    def need(n):
        buf = b""
        while len(buf) < n:
            chunk = sock.recv(n - len(buf))
            if not chunk:
                return None
            buf += chunk
        return buf

    head = need(2)
    if not head:
        return None
    opcode = head[0] & 0x0F
    masked = head[1] & 0x80
    ln = head[1] & 0x7F
    if ln == 126:
        ext = need(2)
        if not ext:
            return None
        ln = struct.unpack(">H", ext)[0]
    elif ln == 127:
        ext = need(8)
        if not ext:
            return None
        ln = struct.unpack(">Q", ext)[0]
    mask = need(4) if masked else None
    data = need(ln) if ln else b""
    if data is None:
        return None
    if mask:
        data = bytes(c ^ mask[i % 4] for i, c in enumerate(data))
    if opcode == 0x8:
        return None
    if opcode not in (0x1, 0x2):
        return ""
    return data.decode("utf-8", "replace")


# ---------------------------------------------------------------------- карт

class FakeKart(threading.Thread):
    daemon = True

    def __init__(self, host, port, duuid, number, pedal, local=False, adc_fault=False,
                 wait=600, io_edge=False):
        threading.Thread.__init__(self, name="kart-%s" % number)
        self.host, self.port = host, port
        self.duuid = duuid
        self.number = number
        self.pedal = pedal
        # Как настоящая плата, которую застали в местном режиме: сервера не
        # было, гость включил I/O и катается сам. Снимает только Stop.
        self.local_ride = local
        # Сбой шины I2C: все каналы АЦП читаются как 255, пока реле включено.
        self.adc_fault = adc_fault
        # Прошивка 0.9.10 после Start ждёт фронта I/O и через 600 с ожидания
        # снимает заезд сама. Каждый Start в ожидании таймер перезапускает.
        self.wait = wait
        # Гость щёлкнул I/O: катание пошло по Length (timeDriveOn=1), и Start
        # его уже не продлевает — только Stop и новый Start.
        self.io_edge = io_edge
        self.time_drive_on = 0
        self.sock = None
        self.max_speed = 60
        self.drive_on = 0
        self.length = 0
        self.drive_until = 0.0
        self.reboots = random.randint(3, 40)
        self.booted = time.time()

    # ---- то, что видит панель
    def telemetry(self):
        relay = 1 if (self.drive_on or self.local_ride) else 0
        moving = relay and self.pedal
        adc_in = random.randint(96, 118) if moving else random.randint(60, 72)
        adc3 = random.randint(128, 152) if moving else random.randint(52, 62)
        adc0 = random.randint(63, 66)
        if self.adc_fault and relay:
            adc_in = adc0 = adc3 = 255
        a_in = random.randint(22, 27) if relay else random.randint(9, 13)
        return {
            "SSDP": "Kart_%d_" % self.number,
            "DUUID": str(self.duuid),
            "Device_name": "Kart",
            "Device_model": "5.1",
            "Firmvare_version": "0.9.10",
            "ip": "10.20.0.%d" % (100 + self.number),
            "driveOn": self.drive_on,
            "kOn": str(relay),
            "kOn1": str(relay),
            "Speed": self.max_speed,
            "remoteMode": 1,
            "blockLokalDrive": 0,
            "lengthDrive": 600 if self.local_ride else self.length,
            "timeDriveOn": 1 if (self.local_ride or self.time_drive_on) else 0,
            "localModeWaitStart": 1 if self.local_ride else 0,
            "adcIn": str(adc_in),
            "adc0": str(adc0),
            "adc3": str(adc3),
            "aIn": "%d_%.2f" % (a_in, a_in * 0.0404),
            "dIn": "1",
            "temperature1": "nan",
            "rssi": str(random.randint(-72, -45)),
            "reboots": self.reboots,
            "uptime": int(time.time() - self.booted),
            "time": time.strftime("%H:%M:%S"),
            "date": time.strftime("%a %b %d %Y"),
        }

    def say(self, obj):
        ws_send(self.sock, obj if isinstance(obj, str)
                else json.dumps(obj, ensure_ascii=False))

    def handle(self, text):
        try:
            cmd = json.loads(text)
        except ValueError:
            return
        if not isinstance(cmd, dict):
            return
        name = cmd.get("Command")

        if name == "Start":
            if "Speed" in cmd:
                self.max_speed = min(100, int(cmd.get("Speed") or 0))
            renewed = not self.time_drive_on
            if renewed:
                self.length = int(cmd.get("Length") or 0)
                # По I/O плата едет Length, потом минуту паркуется на 20% и
                # только тогда роняет реле; без I/O — таймаут ожидания.
                self.drive_until = time.time() + (self.length + 60 if self.io_edge
                                                  else self.wait)
                self.time_drive_on = 1 if self.io_edge else 0
            self.drive_on = 1
            self.say("Start OK")
            print("  карт %-2d  Start на %d с, лимит %d%s"
                  % (self.number, self.length, self.max_speed,
                     "" if renewed else " — идёт катание по I/O, Start его не продлил"))

        elif name == "Stop":
            was_local = self.local_ride
            self.drive_on = 0
            self.length = 0
            self.drive_until = 0
            self.time_drive_on = 0
            self.local_ride = False
            self.say("Stop OK")
            print("  карт %-2d  Stop%s" % (self.number,
                                         " — местное катание снято" if was_local else ""))

        elif name == "MaxSpeed":
            self.max_speed = int(cmd.get("MaxSpeed") or 0)
            self.say("MaxSpeed OK")
            print("  карт %-2d  MaxSpeed %d" % (self.number, self.max_speed))

        elif name == "Status":
            self.say(self.telemetry())
            self.say("Status OK")

        elif name in ("Update", "UpdateFS"):
            self.say("%s OK" % name)
            print("  карт %-2d  %s (подделка, ничего не шьётся)" % (self.number, name))

        else:
            self.say("error")

    # ---- свой таймер: настоящая плата гасит себя сама
    def expire(self):
        if self.drive_on and self.drive_until and time.time() >= self.drive_until:
            print("  карт %-2d  %s, погас сам" % (
                self.number, "катание по Length кончилось" if self.time_drive_on
                else "время ожидания вышло (%d с от Start)" % self.wait))
            self.drive_on = 0
            self.length = 0
            self.drive_until = 0
            self.time_drive_on = 0

    def run(self):
        while True:
            try:
                self.sock = ws_connect(self.host, self.port)
                self.sock.settimeout(1.0)
                self.say({"Command": "Init", "DUUID": self.duuid,
                          "Time": int(time.time())})
                print("  карт %-2d  подключился, DUUID %d" % (self.number, self.duuid))
                while True:
                    try:
                        text = ws_recv(self.sock)
                    except socket.timeout:
                        self.expire()
                        continue
                    if text is None:
                        raise OSError("сервер закрыл соединение")
                    self.expire()
                    if text:
                        self.handle(text)
            except (OSError, ValueError) as e:
                print("  карт %-2d  нет связи (%s), пробую снова через 3 с"
                      % (self.number, e))
                try:
                    if self.sock:
                        self.sock.close()
                except OSError:
                    pass
                self.drive_on = 0
                time.sleep(3)


def main():
    ap = argparse.ArgumentParser(description="Поддельные карты для проверки панели")
    ap.add_argument("--host", default="127.0.0.1", help="адрес сервера (localhost)")
    ap.add_argument("--port", type=int, default=8080, help="порт сервера (8080)")
    ap.add_argument("--karts", type=int, default=3, help="сколько картов (3)")
    ap.add_argument("--first", type=int, default=90000001, help="первый DUUID")
    ap.add_argument("--pedal", action="store_true",
                    help="имитировать нажатую педаль: adcIn и adc3 растут на ходу")
    ap.add_argument("--local", action="store_true",
                    help="карт 1 подключается посреди местного катания без оплаты")
    ap.add_argument("--adc-fault", action="store_true",
                    help="у карта 1 сбой шины I2C: при включённом реле АЦП читается как 255")
    ap.add_argument("--wait", type=int, default=600,
                    help="таймаут ожидания платы после Start, с (у прошивки 600)")
    ap.add_argument("--io-edge", action="store_true",
                    help="на карте 1 гость щёлкает I/O: Start его заезд не продлевает")
    args = ap.parse_args()

    print("=" * 58)
    print("  ПОДДЕЛЬНЫЕ КАРТЫ — проверка сервера без железа")
    print("=" * 58)
    print("  Сервер:  %s:%d" % (args.host, args.port))
    print("  Картов:  %d, DUUID с %d" % (args.karts, args.first))
    print("  Педаль:  %s" % ("нажата" if args.pedal else "отпущена"))
    print()
    print("  Открой панель маршала и запусти заезд.")
    print("  Останов — Ctrl+C")
    print("=" * 58)

    for i in range(args.karts):
        first = i == 0
        FakeKart(args.host, args.port, args.first + i, i + 1, args.pedal,
                 local=first and args.local, adc_fault=first and args.adc_fault,
                 wait=args.wait, io_edge=first and args.io_edge).start()
        time.sleep(0.3)

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nОстановлено.")
        sys.exit(0)


if __name__ == "__main__":
    main()
