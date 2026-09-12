#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
SmartKart — сервер картов и две панели.

Запуск:   python marshal.py
Панели:   http://localhost:8080/        — панель маршала, простая
          http://localhost:8080/admin   — админ-панель, за паролем

Пароль и настройки лежат в marshal.conf рядом с этим файлом.
Файл создаётся сам при первом запуске. Скорости, пресеты времени,
докатку и имена картов можно править прямо из админки — сервер сам
перепишет marshal.conf и применит без перезапуска.

Нужен только Python 3.7+, никаких pip-пакетов.

Что важно знать про устройство:
  * Карты сами подключаются сюда вебсокетом на порт 8080 и ждут команд.
    Адрес сервера зашит в прошивку карта.
  * Телеметрия берётся по вебсокету командой Status, а НЕ по HTTP к карту.
    Прямой HTTP остался только в админке и только для наладки на месте —
    из облака он работать не будет, карт там за NAT.
  * Карт опознаётся по DUUID, а не по IP: адрес после перезагрузки меняется.
"""

import base64
import collections
import hmac
import html
import json
import os
import re
import secrets
import socket
import struct
import sys
import threading
import time
import urllib.error
import urllib.parse
import urllib.request
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

HERE = os.path.dirname(os.path.abspath(__file__))
CONF_PATH = os.path.join(HERE, "marshal.conf")
NO_PROXY = urllib.request.build_opener(urllib.request.ProxyHandler({}))


# ======================================================================== лог
#
# Всё, что сервер печатает, дублируется в файл с меткой времени до
# миллисекунд. Файл новый на каждый час: logs/marshal-2026-09-06_14.log.
#
# Зачем метки: без них по логу нельзя посчитать, сколько прошло между
# командой и ответом, и разбор превращается в гадание по порядку строк.
# Зачем по часу: закрытый файл спокойно уезжает в OneDrive, а открытый
# синхронизация дёргает.
#
# Логи старше LOG_KEEP_DAYS удаляются при запуске.

LOG_DIR = os.path.join(HERE, "logs")
LOG_KEEP_DAYS = 14
LOG_QUEUE_MAX = 20000


class _Tee(object):
    """Складывает строки в очередь. Пишет их отдельный поток.

    ЗАЧЕМ ИМЕННО ТАК. В первой версии write() писал в файл и делал flush
    прямо в том потоке, который позвал print. Файл лежит в OneDrive, и
    когда синхронизация забирала его под замок, вставал не логгер, а весь
    сервер: все потоки упирались в один лок. 06.09 сервер так замерзал
    двадцать раз за смену, самая длинная пауза 1213 секунд. Карты в это
    время стучались в пустоту.

    Тот же эффект даёт режим выделения в консоли Windows: кликнул мышью
    в окно — процесс встал на следующей записи.

    Поэтому ни один поток сервера больше не касается ни файла, ни консоли.
    Он кладёт строку в память и идёт дальше. Тормозит диск, OneDrive или
    консоль — растёт очередь, а парк продолжает ездить.
    """

    _q = collections.deque()
    _wake = threading.Event()
    _started = False
    _dropped = 0

    def __init__(self, stream):
        self.stream = stream
        self.buf = ""
        if not _Tee._started:
            _Tee._started = True
            threading.Thread(target=_Tee._writer, daemon=True).start()

    def write(self, s):
        # Только память. Никаких файлов, никаких локов на запись.
        self.buf += s
        while "\n" in self.buf:
            line, self.buf = self.buf.split("\n", 1)
            now = time.time()
            ts = "%s.%03d" % (time.strftime("%H:%M:%S", time.localtime(now)),
                              int((now % 1) * 1000))
            if len(_Tee._q) >= LOG_QUEUE_MAX:
                _Tee._dropped += 1
                _Tee._q.popleft()
            _Tee._q.append((ts, self.stream, line.rstrip("\r")))
        _Tee._wake.set()

    def flush(self):
        pass

    def isatty(self):
        return False

    @staticmethod
    def _writer():
        fh, hour = None, None
        console = sys.__stdout__
        while True:
            _Tee._wake.wait(1.0)
            _Tee._wake.clear()
            while _Tee._q:
                try:
                    ts, stream, line = _Tee._q.popleft()
                except IndexError:
                    break
                try:
                    console.write(line + "\n")
                except (UnicodeEncodeError, OSError, ValueError):
                    pass
                try:
                    h = time.strftime("%Y-%m-%d_%H")
                    if h != hour:
                        if fh:
                            fh.close()
                        os.makedirs(LOG_DIR, exist_ok=True)
                        fh = open(os.path.join(LOG_DIR, "marshal-%s.log" % h),
                                  "a", encoding="utf-8")
                        hour = h
                    fh.write("%s %s\n" % (ts, line))
                except OSError:
                    fh, hour = None, None      # попробуем на следующей строке
            try:
                if fh:
                    fh.flush()
            except OSError:
                pass


def no_quick_edit():
    """Выключить режим выделения в консоли Windows.

    С ним любой клик мышью в окно сервера морозит процесс до нажатия
    Enter. На кассе в окно кликают случайно, и это выглядит как «всё
    зависло».
    """
    if os.name != "nt":
        return
    try:
        import ctypes
        k = ctypes.windll.kernel32
        h = k.GetStdHandle(-10)                # STD_INPUT_HANDLE
        mode = ctypes.c_uint()
        if k.GetConsoleMode(h, ctypes.byref(mode)):
            k.SetConsoleMode(h, (mode.value & ~0x0040) | 0x0080)
    except Exception:
        pass


def start_file_log():
    try:
        os.makedirs(LOG_DIR, exist_ok=True)
        edge = time.time() - LOG_KEEP_DAYS * 86400
        for name in os.listdir(LOG_DIR):
            path = os.path.join(LOG_DIR, name)
            if name.startswith("marshal-") and os.path.getmtime(path) < edge:
                os.remove(path)
    except OSError:
        pass
    no_quick_edit()
    sys.stdout = _Tee(sys.stdout)
    sys.stderr = _Tee(sys.stderr)


# ======================================================================= конфиг

DEFAULT_CONF = """\
# ============================================================
#  SmartKart — настройки панели маршала
#  Строки ниже можно править руками или прямо из админ-панели.
#  Пароли меняются только здесь.
# ============================================================

# --- доступ -------------------------------------------------
# Админ-панель (http://<адрес>:8080/admin). Смени пароль!
admin_user = admin
admin_pass = CHANGE_ME

# Пароль на казуальную панель маршала.
# Пусто = вход без пароля (удобно, если ПК стоит за стойкой).
marshal_pass =

# --- сеть ---------------------------------------------------
port = 8080
host = 0.0.0.0

# --- заезд (правится из админки) ----------------------------
# Кнопки длительности в панели маршала, минуты через запятую.
presets = 5,10,20,30

# Кнопки тест-драйва — короткие пробные поездки, отдельным рядом.
# Тот же заезд, просто быстро и подписан иначе.
test_presets = 1,2,3

# Градации скорости: подпись:значение. Значение 0..100.
# Маршал видит подпись, число ему знать не нужно.
speeds = Новичок:30, Обычный:60, Быстро:85

# Ограничение скорости на докатке.
# ИЗМЕРЕНО 05.09.2026 на живом карте: программный лимит скорости на этой
# прошивке НЕ РАБОТАЕТ. Карт в докатке едет ровно так же, как в обычном
# заезде. Скоростью управляет физический трёхпозиционник на корпусе.
# Значение ниже сервер по-прежнему шлёт, но на движение оно не влияет,
# и докатка — это теперь просто время доехать до бокса, а не медленный ход.
speed_crawl = 15

# Сколько секунд длится докатка после конца оплаченного времени.
# Карт гаснет сам по её истечении.
crawl_seconds = 60

# --- разрешение движения ------------------------------------
# Часть картов не едет, пока на плате не поднят выход, разрешающий
# движение. Сервер дёргает его сам: поднимает перед стартом заезда
# и снимает по его окончании, чтобы это нельзя было забыть включённым.
# Идёт по HTTP прямо к плате, значит сервер должен до неё доставать.
# Пусто в drive_on = ничего не дёргать.
drive_on = On6
drive_off = Off6

# Сколько секунд ждать плату при этом. Мало — старт не будет
# подвисать, если карт не отвечает.
drive_timeout = 3

# Пауза после разрешения, прежде чем слать лимит скорости.
# Плата после запроса к своим выходам успевает переписать настройки,
# и лимит, посланный слишком рано, затирается в ноль.
drive_settle = 0.6

# Дублировать лимит скорости запросом по HTTP после вебсокетного.
# HTTP на этой прошивке главнее вебсокета, поэтому последнее слово
# должно быть за ним. Работает только для картов, до которых сервер
# достаёт по HTTP — то есть там же, где работает разрешение движения.
speed_http = yes

# Как делать докатку.
#   restart — погасить карт, заново поднять разрешение движения, выставить
#             низкий лимит и запустить снова. Нужно потому, что лимит на этой
#             прошивке берётся в момент старта поездки.
#   live    — только сменить лимит и продлить поездку, ничего не гася.
#             Так было раньше; скорость при этом не падала.
crawl_mode = restart

# Как часто спрашивать телеметрию у каждого карта, секунды. Опрос
# размазывается по всему периоду, по одному карту за раз. Телеметрия
# нужна только для экрана; ехать карту она не помогает, а лишние
# запросы к ESP8266 обрывают связь. Меньше 2 нельзя, по умолчанию 6.
status_period = 6

# --- веб-морда карта (нужна только админке для наладки) ------
kart_user = admin
kart_pass = esp8266esp

# --- имена картов (правится из админки) ---------------------
# Номер на кузове напротив DUUID, чтобы маршал видел «Карт 4».
kart.14851750 = 4
"""

conf_lock = threading.Lock()


def read_conf():
    if not os.path.exists(CONF_PATH):
        with open(CONF_PATH, "w", encoding="utf-8") as fh:
            fh.write(DEFAULT_CONF)
        print("  Создан %s — там пароль, смени его." % CONF_PATH)
    conf = {}
    with open(CONF_PATH, encoding="utf-8") as fh:
        for line in fh:
            line = line.split("#", 1)[0].strip()
            if not line or "=" not in line:
                continue
            k, v = line.split("=", 1)
            conf[k.strip()] = v.strip()
    return conf


CONF = read_conf()


def cint(key, default):
    try:
        return int(str(CONF.get(key, default)).strip())
    except (TypeError, ValueError):
        return default


def cstr(key, default=""):
    return CONF.get(key, default)


def cfloat(key, default):
    try:
        return float(str(CONF.get(key, default)).strip().replace(",", "."))
    except (TypeError, ValueError):
        return default


def parse_presets(text, fallback):
    out = []
    for part in str(text).split(","):
        part = part.strip()
        if part.isdigit() and 1 <= int(part) <= 180:
            out.append(int(part))
    return out[:6] or list(fallback)


def parse_speeds(text, fallback):
    out = []
    for part in str(text).split(","):
        part = part.strip()
        if ":" not in part:
            continue
        name, val = part.rsplit(":", 1)
        name = name.strip()[:16]
        try:
            val = max(0, min(100, int(val.strip())))
        except ValueError:
            continue
        if name:
            out.append({"name": name, "val": val})
    return out[:4] or [dict(s) for s in fallback]


DEF_SPEEDS = [{"name": "Новичок", "val": 30},
              {"name": "Обычный", "val": 60},
              {"name": "Быстро", "val": 85}]

# Живые настройки. Меняются из админки, тогда же переписывается marshal.conf.
S = {
    "presets": parse_presets(cstr("presets", "5,10,20,30"), [5, 10, 20, 30]),
    # Пустая строка в конфиге = тест-драйв выключен, ряд кнопок пропадёт.
    # Строки нет совсем (старый конфиг) = включаем со значениями по умолчанию.
    "test_presets": (parse_presets(cstr("test_presets"), [])
                     if "test_presets" in CONF else [1, 2, 3]),
    "speeds": parse_speeds(cstr("speeds", ""), DEF_SPEEDS),
    "speed_crawl": max(0, min(100, cint("speed_crawl", 15))),
    "drive_on": cstr("drive_on", "On6").strip(),
    "drive_off": cstr("drive_off", "").strip(),
    "drive_timeout": max(1, min(20, cint("drive_timeout", 3))),
    "drive_settle": max(0.0, min(5.0, cfloat("drive_settle", 0.6))),
    "speed_http": cstr("speed_http", "no").strip().lower()
                  in ("yes", "1", "true", "да"),
    "crawl_seconds": max(0, min(3600, cint("crawl_seconds", 0))),
    # Прошивка гасит заезд на 600 секундах, что бы ей ни прислали
    # (измерено 06.09). Длинный заезд сервер режет на куски и
    # перезапускает за chunk_lead секунд до конца каждого.
    # Лимит скорости 0..100. Отдельный на карт живёт в karts.conf,
    # здесь — значение для карта, которому ещё ничего не задали.
    "speed_default": max(0, min(100, cint("speed_default", 50))),
    # Токен для внешних систем: CRM, боты. Пустой = внешний API выключен.
    "api_token": cstr("api_token", "").strip(),
    "chunk_seconds": max(0, min(3600, cint("chunk_seconds", 540))),
    "chunk_lead": max(2, min(60, cint("chunk_lead", 8))),
    # Выход 7: обычная скорость и докаточная. На нём подсветка и реле
    # режима контроллера. Пусто — сервер выход 7 не трогает вообще.
    "speed_fast": cstr("speed_fast", "On7").strip(),
    "speed_slow": cstr("speed_slow", "Off7").strip(),
    # Как часто спрашивать у картов телеметрию. Раньше было жёстко 3 секунды
    # и по четверти секунды между картами: на пятнадцати картах это почти
    # непрерывный поток запросов к ESP8266, которая такого не любит и рвёт
    # связь. Телеметрия нужна только чтобы видеть карт на экране, ехать она
    # не помогает — так что реже здесь лучше.
    "status_period": max(2, min(60, cint("status_period", 6))),
    "crawl_mode": ("live" if cstr("crawl_mode", "restart").strip().lower()
                   == "live" else "restart"),
}
# ---------------------------------------------------------------- имена картов
#
# Имена (номер на кузове) живут в ОТДЕЛЬНОМ файле karts.conf рядом с
# marshal.py, а не в marshal.conf. Причина простая: marshal.conf меняется
# часто и его присылают новыми версиями целиком, а разметка парка —
# двенадцать строк, которые вбиваются руками и терять их нельзя.
#
# Формат — по строке на карт:
#     14851750 = 4
#     13356403 = 7
#
# Старые строки `kart.<DUUID> = номер` из marshal.conf по-прежнему читаются,
# так что ничего вручную переносить не нужно: при первом же сохранении из
# админки они сами переедут в karts.conf.
NAMES_PATH = os.path.join(HERE, "karts.conf")
names_lock = threading.Lock()


def read_names():
    """Читает karts.conf: имена и personal лимит скорости каждого карта.

    Формат:
        14851750       = 10      номер на кузове
        14851750.speed = 50      лимит maxSpeed для этого карта

    Лимит живёт здесь, а не в marshal.conf, по той же причине, что и
    имена: общий конфиг заменяется целиком, а разметка парка нет.
    """
    out = {k[5:].strip(): v.strip() for k, v in CONF.items()
           if k.startswith("kart.")}
    speed = {}
    try:
        with open(NAMES_PATH, encoding="utf-8") as fh:
            for line in fh:
                line = line.split("#", 1)[0].strip()
                if not line or "=" not in line:
                    continue
                key, val = line.split("=", 1)
                key, val = key.strip(), val.strip()
                if not key:
                    continue
                if key.endswith(".speed"):
                    try:
                        speed[key[:-6]] = max(0, min(100, int(val)))
                    except ValueError:
                        pass
                else:
                    out[key] = val         # файл имён главнее старого конфига
    except OSError:
        pass
    return out, speed


def write_names(names, speed=None):
    if speed is None:
        speed = KART_SPEED
    with names_lock:
        out = ["# Карты парка. Этот файл при обновлении сервера не заменяется.",
               "#   <DUUID>       = номер на кузове",
               "#   <DUUID>.speed = лимит скорости 0..100",
               "# Правится из панели и админки.",
               ""]
        for duuid in sorted(set(list(names) + list(speed))):
            if str(names.get(duuid, "")).strip():
                out.append("%s = %s" % (duuid, names[duuid]))
            if duuid in speed:
                out.append("%s.speed = %d" % (duuid, speed[duuid]))
        out.append("")
        tmp = NAMES_PATH + ".tmp"
        with open(tmp, "w", encoding="utf-8") as fh:
            fh.write("\n".join(out))
        os.replace(tmp, NAMES_PATH)


KART_NAMES, KART_SPEED = read_names()


def kart_speed(duuid):
    """Лимит скорости конкретного карта. Нет своего — берём общий."""
    return KART_SPEED.get(str(duuid), S["speed_default"])

# Куда сервер стучится к плате по HTTP, если её собственный адрес ему
# недоступен. Нужно, когда карты за NAT и до них пробрасываются порты:
#     http.14851750 = 192.168.88.48:8001
# Пусто — берём адрес из телеметрии самой платы.
KART_HTTP = {k[5:].strip(): v.strip() for k, v in CONF.items()
             if k.startswith("http.")}


def write_conf(new_presets, new_test, new_speeds, crawl_speed, crawl_sec, names):
    """Переписывает marshal.conf, сохраняя комментарии и пароли.

    Имена картов сюда БОЛЬШЕ НЕ ПИШУТСЯ — они живут в karts.conf, который
    при замене marshal.conf не трогается. Раньше `kart.<DUUID> = номер`
    лежали в общем конфиге, и каждая присланная новая версия конфига
    стирала всю разметку парка. Забивать двенадцать номеров заново — гемор,
    которого не должно быть.
    """
    write_names(names)
    with conf_lock:
        with open(CONF_PATH, encoding="utf-8") as fh:
            lines = fh.read().splitlines()

        repl = {
            "presets": ",".join(str(p) for p in new_presets),
            "test_presets": ",".join(str(p) for p in new_test),
            "speeds": ", ".join("%s:%d" % (s["name"], s["val"]) for s in new_speeds),
            "speed_crawl": str(crawl_speed),
            "crawl_seconds": str(crawl_sec),
        }
        seen = set()
        out = []
        for line in lines:
            m = re.match(r"^(\s*)([A-Za-z_][\w.]*)(\s*)=(.*)$", line)
            if not m:
                if line.strip().startswith("# --- имена картов"):
                    continue          # старый заголовок блока имён больше не нужен
                out.append(line)
                continue
            key = m.group(2)
            if key in repl:
                out.append("%s = %s" % (key, repl[key]))
                seen.add(key)
            elif key.startswith("kart."):
                continue              # имена переехали в karts.conf
            else:
                out.append(line)

        for key, val in repl.items():
            if key not in seen:
                out.append("%s = %s" % (key, val))

        while out and not out[-1].strip():
            out.pop()
        out.append("")

        tmp = CONF_PATH + ".tmp"
        with open(tmp, "w", encoding="utf-8") as fh:
            fh.write("\n".join(out))
        os.replace(tmp, CONF_PATH)


# ==================================================================== вебсокет

WS_GUID = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
WS_LOG_MAX = 400

karts = {}
karts_lock = threading.RLock()

# Карты, потерявшие связь. Соединение рвётся от любого провала сигнала,
# и объект карта умирает вместе с заездом — карточка исчезала из панели
# целиком, а через несколько секунд появлялась снова. Маршал видел это
# как «карты мигают, таймер врёт».
#
# Здесь остаётся слепок: имя, заезд, последняя телеметрия, время последнего
# контакта. Панель рисует из него карточку «нет связи» с идущим таймером,
# а вернувшийся карт забирает свой заезд обратно. Ключ — DUUID: IP после
# перезагрузки меняется, DUUID нет.
ghosts = {}
GHOST_TTL = 600          # сколько держать пропавший карт в панели, секунд
ws_log = []
ws_lock = threading.Lock()


# Поля телеметрии, ради которых лог вообще читают. Порядок — как смотрят
# глазами: сначала едет или нет, потом лимит, потом входы и связь.
BRIEF_KEYS = ("driveOn", "Speed", "lengthDrive", "timeDriveOn",
              # Прошивка умеет ездить и без сервера: у неё есть локальный
              # режим со своим таймером и своими кнопками на корпусе.
              # Эти поля я раньше выбрасывал из лога — и мы оба не видели,
              # в каком режиме на самом деле находится карт.
              "remoteMode", "localModeStart", "localModeWaitStart",
              "localModeDriveON", "blockLokalDrive", "localDrivesCount",
              "DrivePoints", "timeParking",
              "kOn", "kOn1", "adcIn", "adc0", "adc3", "aIn", "dIn",
              "rssi", "reboots", "uptime")

# Те же поля, но короче — для строки сверки во время заезда.
KART_TIME_KEYS = ("driveOn", "lengthDrive", "timeDriveOn", "Speed")


def status_brief(obj):
    """Сжать ответ Status до одной читаемой строки.

    Сырой JSON платы — это 700 символов, из которых 90% всегда одинаковы,
    а нужные поля лежат в конце и обрезаются консолью. Полная телеметрия
    никуда не девается: она видна в админке, в «живых полях».
    """
    parts = ["%s=%s" % (k, obj[k]) for k in BRIEF_KEYS if k in obj]
    return "Status  " + "  ".join(parts) if parts else ""


def wslog(direction, kart_id, text):
    with ws_lock:
        ws_log.append({"t": time.strftime("%H:%M:%S"), "dir": direction,
                       "kart": kart_id, "text": text[:2000]})
        del ws_log[:-WS_LOG_MAX]
    print("  WS %-3s %-14s %s" % (direction, kart_id, text[:2000]))


def ws_accept_key(key):
    import hashlib
    return base64.b64encode(hashlib.sha1((key + WS_GUID).encode()).digest()).decode()


def ws_read_frame(rfile):
    hdr = rfile.read(2)
    if not hdr or len(hdr) < 2:
        return None
    b1, b2 = hdr[0], hdr[1]
    opcode, masked, ln = b1 & 0x0F, b2 & 0x80, b2 & 0x7F
    if ln == 126:
        ext = rfile.read(2)
        if len(ext) < 2:
            return None
        ln = struct.unpack(">H", ext)[0]
    elif ln == 127:
        ext = rfile.read(8)
        if len(ext) < 8:
            return None
        ln = struct.unpack(">Q", ext)[0]
    mask = rfile.read(4) if masked else None
    data = b""
    while len(data) < ln:
        chunk = rfile.read(ln - len(data))
        if not chunk:
            return None
        data += chunk
    if mask:
        data = bytes(c ^ mask[i % 4] for i, c in enumerate(data))
    return opcode, data


def ws_write_frame(wfile, opcode, data=b""):
    out = bytearray([0x80 | opcode])
    n = len(data)
    if n < 126:
        out.append(n)
    elif n < 65536:
        out.append(126)
        out += struct.pack(">H", n)
    else:
        out.append(127)
        out += struct.pack(">Q", n)
    out += data
    wfile.write(bytes(out))
    wfile.flush()


def ws_send(kart, obj):
    text = obj if isinstance(obj, str) else json.dumps(obj, ensure_ascii=False)
    # Карт уже отвалился — писать некуда. Раньше это давало WinError 10038
    # («операция на объекте, не являющемся сокетом»): 37 раз за два часа.
    if kart.get("duuid") and not kart_online(kart):
        return False
    try:
        with kart["lock"]:
            ws_write_frame(kart["wfile"], 0x1, text.encode("utf-8"))
    except (OSError, ValueError) as e:
        wslog("sys", kart["id"], "ошибка отправки: %s" % e)
        return False
    wslog("out", kart["id"], text)
    return True


def find_kart(key):
    with karts_lock:
        return karts.get(key)


def all_karts():
    with karts_lock:
        return list(karts.values())


# Карты, до которых сейчас не достучаться. Пока карт здесь, HTTP-команды
# ему не шлются вовсе: каждая такая попытка занимает ОБЩИЙ шлюз на время
# таймаута, и парк из-за одной отвалившейся платы встаёт целиком.
# По логам 09.09 в 19:32-19:35 шлюз был занят мёртвыми платами по 50-57
# секунд из каждых 60, и доля непрошедших команд доходила до 100%.
# Карты, которым обязаны снять разрешение движения. Заезд закончился,
# а плата была не на связи — команда ждёт здесь и уходит при первом же
# возвращении. Без этого карт остаётся на ходу после конца заезда.
pending_stop = set()
pending_stop_lock = threading.Lock()

unreachable = {}                 # duuid -> когда пробовать снова
unreachable_lock = threading.Lock()
UNREACHABLE_FAILS = 2            # столько отказов подряд, и плата в отставке
UNREACHABLE_HOLD = 20.0          # на столько секунд, если не подключится раньше
_http_fails = collections.Counter()


def kart_online(kart):
    """Этот ли объект карта сейчас в реестре.

    Отвалившийся карт из реестра удаляется, но ссылку на него может ещё
    держать поток докатки или восстановления. Отправлять по ней бесполезно:
    сокет закрыт, а HTTP уйдёт в таймаут.
    """
    duuid = kart.get("duuid")
    if not duuid:
        return False
    with karts_lock:
        return karts.get(duuid) is kart



# ===================================================== желаемое состояние
#
# Сервер не «выполняет команды». Он помнит, каким карт ДОЛЖЕН быть, и
# приводит его к этому виду. Полей ровно два, и оба видны в телеметрии:
#
#     gate  — поднято ли разрешение движения   (подтверждается kOn)
#     speed — какой лимит скорости, в процентах (подтверждается Speed)
#     light — поднят ли выход 7                 (подтверждается kOn1)
#
# Почему так, а не «послать и забыть». Связь рвётся каждые полторы-три
# минуты, плата не отвечает на часть запросов, и любая отправка может не
# дойти. Раньше на это отвечали повторами, разбросанными по пяти разным
# процедурам, а команду недоступной плате просто выбрасывали — отсюда
# рывки: карт не получал разрешения и стоял до следующей случайной попытки.
#
# Теперь неотправленная команда не теряется: желаемое остаётся, и фоновый
# цикл досылает его, когда плата вернётся. А если телеметрия говорит, что
# карт УЖЕ в нужном состоянии, команда не отправляется вовсе — это само по
# себе убирает большую часть запросов к плате.

want = {}                        # duuid -> {"gate": bool|None, "speed": int|None}
want_lock = threading.Lock()
WANT_TICK = 2.0                  # как часто сверяем желаемое с телеметрией


def want_set(kart, **fields):
    duuid = str(kart.get("duuid") or kart.get("id") or "")
    if not duuid:
        return
    with want_lock:
        w = want.setdefault(duuid, {})
        w.update(fields)
        w["tries"] = 0
        w["next_try"] = 0


def want_clear(duuid, field):
    with want_lock:
        w = want.get(duuid)
        if w:
            w.pop(field, None)
            if not any(k in w for k in ("gate", "speed", "light")):
                want.pop(duuid, None)


def speed_raw(pct):
    """Шкала maxSpeed у платы — 0..100, то есть те же проценты.

    12.09: до этого сервер множил проценты на 2.55, потому что подпись
    «(0..255)» в веб-морде платы была взята от соседней строки. Дословно
    там так:

        Аналог. вход(0..1024) = aIn
        АЦП вход(0..255)      = adcIn
        ЦАП выход(0..255)     = adc0
        Максимальная скорость = Speed      ← диапазона нет

    Диапазон 0..255 относится к АЦП и ЦАП, а не к maxSpeed. Заводской
    config.json хранит "maxSpeed":70, на другом карте 60 — это проценты.

    Из-за множителя всё выше 40% превращалось в значение больше 100,
    плата обрезала его до своего потолка и рапортовала Speed=100. Отсюда
    и «карт не слушает регулировку»: любая скорость выше 40% давала
    полный газ.
    """
    return max(0, min(100, int(round(pct))))


def want_done(kart):
    """Что из желаемого уже подтверждено телеметрией."""
    duuid = str(kart.get("duuid") or "")
    with want_lock:
        w = dict(want.get(duuid) or {})
    if not w:
        return
    st = kart.get("status") or {}
    if "gate" in w and w["gate"] is not None:
        kon = str(st.get("kOn", "")).strip()
        if kon in ("0", "1") and (kon == "1") == bool(w["gate"]):
            want_clear(duuid, "gate")
    # Лимит по телеметрии НЕ сверяем: поле Speed во время заезда живёт
    # своей жизнью (см. комментарий в send_speed_now). Подтверждение
    # лимита приходит из успешного ответа платы.
    if "light" in w and w["light"] is not None:
        k1 = str(st.get("kOn1", "")).strip()
        if k1 in ("0", "1") and (k1 == "1") == bool(w["light"]):
            want_clear(duuid, "light")


WANT_TRIES = 4                   # столько досылок, дальше сдаёмся и пишем в лог
WANT_BACKOFF = (3, 8, 20, 40)    # пауза перед каждой следующей попыткой


def want_loop():
    """Один круг — одна команда на карт. Пачек не бывает по построению.

    Досылка не бесконечна. Если телеметрия шесть раз подряд не подтвердила
    желаемое, мы сдаёмся и говорим об этом вслух: значит дело не в потерянном
    запросе, а в плате, и молча долбить её каждые две секунды вредно.
    """
    while True:
        time.sleep(WANT_TICK)
        now = time.time()
        try:
            with want_lock:
                pending = [(d, dict(w)) for d, w in want.items()
                           if any(k in w for k in ("gate", "speed", "light"))]
            for duuid, w in pending:
                if now < w.get("next_try", 0):
                    continue
                kart = karts.get(duuid)
                if not kart or not kart_online(kart) or not kart_reachable(kart):
                    continue                      # не потеряли — досылаем позже
                if not kart_ip(kart) or not kart.get("status"):
                    continue      # телеметрии ещё не было — сравнивать не с чем
                n = int(w.get("tries", 0))
                if n >= WANT_TRIES:
                    field = ("разрешение движения" if w.get("gate") is not None
                             else "лимит" if w.get("speed") is not None
                             else "выход 7")
                    wslog("sys", duuid,
                          "СДАЮСЬ: %s не подтвердилось за %d попыток — смотри плату"
                          % (field, WANT_TRIES))
                    with want_lock:
                        want.pop(duuid, None)
                    continue
                with want_lock:
                    if duuid in want:
                        want[duuid]["tries"] = n + 1
                        want[duuid]["next_try"] = now + WANT_BACKOFF[min(n, len(WANT_BACKOFF) - 1)]
                # Разрешение движения важнее лимита: без него карт не поедет.
                if w.get("gate") is not None:
                    send_gate_now(kart, bool(w["gate"]))
                elif w.get("speed") is not None:
                    send_speed_now(kart, int(w["speed"]))
                elif w.get("light") is not None:
                    send_light_now(kart, bool(w["light"]))
        except Exception as e:
            try:
                wslog("sys", "*", "цикл желаемого состояния: %s" % e)
            except Exception:
                pass


def kart_reachable(kart):
    """Стоит ли вообще пытаться достучаться до платы по HTTP."""
    duuid = kart.get("duuid")
    if not duuid:
        return True
    with unreachable_lock:
        until = unreachable.get(duuid)
        if until and time.time() < until:
            return False
        if until:
            unreachable.pop(duuid, None)
    return True


def http_result(kart, ok):
    """Запомнить исход HTTP-команды и увести плату в отставку, если молчит."""
    duuid = kart.get("duuid")
    if not duuid:
        return
    with unreachable_lock:
        if ok:
            _http_fails.pop(duuid, None)
            unreachable.pop(duuid, None)
            return
        _http_fails[duuid] += 1
        if _http_fails[duuid] >= UNREACHABLE_FAILS:
            unreachable[duuid] = time.time() + UNREACHABLE_HOLD


def kart_back(duuid):
    """Плата снова на связи — снимаем отставку немедленно."""
    with unreachable_lock:
        unreachable.pop(duuid, None)
        _http_fails.pop(duuid, None)


def live_kart(kart):
    """Тот же карт, но его нынешнее соединение.

    Потоки докатки и восстановления живут секундами, а карт за это время
    успевает отвалиться и подключиться заново. Объект при этом создаётся
    новый, а поток продолжает держать старый — с мёртвым сокетом и
    замороженной телеметрией. Команды уходили в никуда, а по старым
    показаниям сервер решал, что докатка не пошла, и слал всё заново.
    Поэтому перед каждым шагом спрашиваем реестр заново.
    """
    duuid = kart.get("duuid")
    if not duuid:
        return kart
    with karts_lock:
        return karts.get(duuid) or kart


IDLE = {"phase": "idle", "minutes": 0, "speed": 0, "t0": 0, "t_paid": 0,
        "t_end": 0, "test": False}


def ride_alive(r, now=None):
    """Заезд, который ещё имеет смысл продолжать.

    Слепок отвалившегося карта может пролежать сколько угодно, и в нём
    может оказаться заезд из прошлой жизни — давно оплаченный, давно
    закончившийся. Раньше такой заезд возвращался карту при подключении:
    карт ни с того ни с сего уходил в докатку, а панель показывала время,
    которого нет. Отсюда «таймер врёт». Проверяем по собственному концу
    заезда, а не по тому, как давно он лежит.
    """
    r = r or {}
    if r.get("phase", "idle") not in ("ride", "crawl"):
        return False
    end = r.get("t_end") or r.get("t_paid") or 0
    return end > (time.time() if now is None else now) + 2


def ghost_drop(key):
    """Забыть слепок: заезд кончился, возвращать нечего."""
    with karts_lock:
        ghosts.pop(str(key or ""), None)


# ======================================================================= заезд
# Докатка живёт здесь, на сервере: в прошивке такой функции нет.
#
#   1. MaxSpeed выбранной градации, затем Start с Length = оплаченное время
#   2. карт гаснет сам по своему таймеру
#   3. сервер сразу шлёт MaxSpeed поменьше и второй Start на окно докатки
#   4. карт гаснет сам окончательно
#
# Два Start, а не один длинный, специально: если сервер упадёт, карт
# остановится по своему таймеру в конце оплаченного времени, а не будет
# ездить на полной скорости лишнюю минуту. Отказ должен быть безопасным.

def kart_ip(kart):
    """Куда стучаться к плате по HTTP.

    Обычно это адрес из её же телеметрии — DHCP его меняет, и брать
    оттуда правильнее всего. Но если карт за NAT и до него проброшен
    порт, адрес прописывается руками строкой http.<DUUID> в marshal.conf,
    и она главнее.
    """
    forced = KART_HTTP.get(kart.get("duuid", ""))
    if forced:
        return forced
    return str((kart.get("status") or {}).get("ip") or "")


def send_light_now(kart, on):
    """Один запрос выхода 7. Повторы делает want_loop."""
    path = S["speed_fast"] if on else S["speed_slow"]
    ip = kart_ip(kart)
    if not path or not ip:
        return
    r = kart_http(ip, path, timeout=S["drive_timeout"])
    http_result(kart, bool(r.get("ok")))
    if r.get("ok"):
        want_clear(str(kart.get("duuid") or ""), "light")
    wslog("sys", kart["id"], "выход 7 %s → %s — %s" % (
        "поднят" if on else "снят", r.get("url") or ip,
        "ок" if r.get("ok") else
        ("НЕ ПРОШЛО: %s" % (r.get("error") or ("код %s" % r.get("status"))))))


def speed_gate(kart, fast, wait=False):
    """Выход 7: подсветка и, если поставлено реле, режим контроллера.

        /On7  → подсветка горит          — обычный заезд
        /Off7 → подсветка гаснет         — докатка

    Так это делал вендор: на докатке гасла подсветка. Клиент по ней и
    понимает, что оплаченное время вышло.

    Как и всё остальное, идёт через желаемое состояние: не дошло —
    досылается, уже стоит нужное по kOn1 — не отправляется вовсе.
    """
    want_set(kart, light=bool(fast))
    st = kart.get("status") or {}
    k1 = str(st.get("kOn1", "")).strip()
    if k1 in ("0", "1") and (k1 == "1") == bool(fast):
        want_clear(str(kart.get("duuid") or ""), "light")
        return
    if not kart_online(kart) or not kart_reachable(kart):
        return
    send_light_now(kart, bool(fast))

def send_gate_now(kart, allow):
    """Один запрос разрешения движения. Без повторов — их делает want_loop."""
    path = S["drive_on"] if allow else S["drive_off"]
    if not path and not allow:
        path = (S["drive_on"] or "").replace("On", "Off")
    ip = kart_ip(kart)
    if not path or not ip:
        return
    r = kart_http(ip, path, timeout=S["drive_timeout"])
    http_result(kart, bool(r.get("ok")))
    if r.get("ok"):
        want_clear(str(kart.get("duuid") or ""), "gate")
    wslog("sys", kart["id"], "%s → %s — %s" % (
        "разрешаю движение" if allow else "снимаю разрешение",
        r.get("url") or ip,
        "ок" if r.get("ok") else
        ("НЕ ПРОШЛО: %s" % (r.get("error") or ("код %s" % r.get("status"))))))


def drive_gate(kart, allow, wait=True):
    """Запомнить, что разрешение должно быть таким, и попробовать сейчас.

    Ничего не теряется: если плата молчит, желаемое останется и досылается
    циклом. Если телеметрия уже показывает нужное состояние, запрос не
    уйдёт вообще.
    """
    want_set(kart, gate=bool(allow))
    st = kart.get("status") or {}
    kon = str(st.get("kOn", "")).strip()
    if kon in ("0", "1") and (kon == "1") == bool(allow):
        want_clear(str(kart.get("duuid") or ""), "gate")
        return
    if not kart_online(kart) or not kart_reachable(kart):
        wslog("sys", kart["id"], "%s отложено: карт не на связи, дошлю сам"
              % ("разрешение движения" if allow else "СТОП"))
        return
    if wait:
        send_gate_now(kart, allow)
    else:
        threading.Thread(target=lambda: send_gate_now(kart, allow),
                         daemon=True).start()

def send_speed_now(kart, pct):
    """Один запрос лимита. Ноль = снять разрешение, это настоящая пауза."""
    ip = kart_ip(kart)
    if not ip:
        return
    # Ноль шлём лимитом. Измерено 10.09, уже после того как ЦАП завели
    # в цепь газа: maxSpeed=0 останавливает плату. Раньше, когда педаль
    # шла в контроллер мимо платы, ноль ничего не значил и останов
    # приходилось делать снятием разрешения.
    raw = speed_raw(pct)
    r = kart_http(ip, "maxSpeed?maxSpeed=%d" % raw, timeout=S["drive_timeout"])
    http_result(kart, bool(r.get("ok")))

    # Лимит считается поставленным по УСПЕШНОМУ ОТВЕТУ ПЛАТЫ, а не по
    # телеметрии.
    #
    # Измерено 12.09: во время заезда поле Speed не отражает заданный
    # лимит. До Start оно равно сохранённому значению, после Start встаёт
    # на 100 и больше не меняется, хотя каждый /maxSpeed возвращает «ок».
    # Проверка по телеметрии в такой ситуации не подтверждается никогда:
    # цикл слал лимит шесть раз подряд и писал СДАЮСЬ, 57 запросов на
    # шесть заездов. Очередь при этом забивалась, и продление куска
    # опаздывало — карт гас раньше времени.
    if r.get("ok"):
        want_clear(str(kart.get("duuid") or ""), "speed")
    wslog("sys", kart["id"], "лимит %d%% → %s — %s" % (
        pct, r.get("url") or ip,
        "ок" if r.get("ok") else
        ("НЕ ПРОШЛО: %s" % (r.get("error") or ("код %s" % r.get("status"))))))


def set_speed_http(kart, value):
    """Запомнить желаемый лимит и попробовать поставить его сейчас.

    Не дошло — не потеряно, досылается циклом. Подтверждением служит
    успешный ответ платы: телеметрия для лимита не годится, поле Speed
    во время заезда показывает не то, что мы задали.
    """
    if not S["speed_http"]:
        return
    pct = max(0, min(100, int(value)))
    want_set(kart, speed=pct)
    if not kart_online(kart) or not kart_reachable(kart):
        wslog("sys", kart["id"], "лимит %d%% отложен: карт не на связи, дошлю сам" % pct)
        return
    send_speed_now(kart, pct)

def kart_num(st, key):
    try:
        return int(str((st or {}).get(key, "")).strip())
    except (TypeError, ValueError):
        return None


def kart_time_brief(st):
    parts = ["%s=%s" % (k, st[k]) for k in KART_TIME_KEYS if k in (st or {})]
    return " ".join(parts) or "телеметрии нет"


def ride_watch(kart, st):
    """Сверка: сколько осталось по мнению сервера и по мнению самого карта.

    Пишется в лог на каждый ответ Status, пока идёт заезд. Нужна затем,
    чтобы спор «таймер врёт» решался числами, а не ощущениями: если сервер
    и плата расходятся, здесь сразу видно, на сколько и в какую сторону.
    А заодно видно, какое из двух полей на самом деле считает время —
    lengthDrive убывает само или растёт timeDriveOn. Пока это не измерено
    на живом карте, ни одна из версий не имеет права попасть в код.
    """
    r = kart.get("ride") or {}
    phase = r.get("phase", "idle")
    if phase not in ("ride", "crawl"):
        return
    srv = int((r.get("t_end", 0) if phase == "crawl"
               else r.get("t_paid", 0)) - time.time())
    ln, td = kart_num(st, "lengthDrive"), kart_num(st, "timeDriveOn")
    ways = []
    if ln is not None and td is not None:
        ways.append("lengthDrive−timeDriveOn=%d" % (ln - td))
    if ln is not None:
        ways.append("lengthDrive=%d" % ln)
    wslog("sys", kart["id"], "СВЕРКА %s: сервер %d с | карт %s | %s"
          % (phase, srv, kart_time_brief(st), ", ".join(ways) or "нечего сверять"))


def ride_resume(kart):
    """Дослать заезд карту, который только что вернулся на связь.

    Если карт всего лишь терял вебсокет, у него уцелел собственный таймер
    и он всё это время ехал — тогда команда просто подтвердит то, что уже
    есть. А если он перезагрузился, то потерял и driveOn, и лимит, и встал
    бы посреди трассы. Поэтому досылаем всегда, с оставшимся временем.
    """
    r = kart.get("ride") or {}
    phase = r.get("phase", "idle")
    if phase not in ("ride", "crawl"):
        return

    def rest_now():
        r2 = live_kart(kart).get("ride") or {}
        if r2.get("phase") != phase:
            return None
        return int((r2.get("t_end", 0) if phase == "crawl"
                    else r2.get("t_paid", 0)) - time.time())

    def go():
        # Сначала СПРАШИВАЕМ карт, едет ли он, и только потом решаем.
        #
        # В прошлой версии я досылал Start вслепую на каждое возвращение
        # связи. Это было неправильно: как прошивка складывает новый Length
        # с уже накопленным timeDriveOn — не проверено ни разу, а карты
        # отваливаются десятки раз за заезд. Едущий карт трогать не за чем:
        # у него свой таймер, он и так доедет.
        asked = time.time()
        k = live_kart(kart)
        ws_send(k, {"Command": "Status"})
        st = {}
        for _ in range(20):
            time.sleep(0.25)
            k = live_kart(kart)
            if k.get("status_at", 0) >= asked:
                st = k.get("status") or {}
                break

        rest = rest_now()
        if rest is None or rest < 3:
            return
        k = live_kart(kart)
        if str(st.get("driveOn", "0")) == "1":
            wslog("sys", k["id"],
                  "вернулся на связь и едет сам — не трогаю. "
                  "У сервера %d с, карт: %s" % (rest, kart_time_brief(st)))
            return

        # Карт стоит, а заезд по нашим часам ещё идёт: значит он
        # перезагрузился и потерял разрешение, лимит и свой таймер.
        # Вот теперь заезд действительно надо вернуть.
        speed = (S["speed_crawl"] if phase == "crawl"
                 else kart_speed(k.get("duuid")))
        drive_gate(k, True)
        if S["drive_settle"]:
            time.sleep(S["drive_settle"])
        # Остаток считаем в последний момент: выше были HTTP-запросы
        # со своими таймаутами, и за это время часы сервера ушли вперёд.
        rest = rest_now()
        if rest is None or rest < 3:
            return
        k = live_kart(kart)
        ws_send(k, {"Command": "Start", "Length": rest})
        time.sleep(0.3)
        k = live_kart(kart)
        if phase == "crawl":
            speed_gate(k, False)          # вернулся на докатке — свет обратно гасим
        set_speed_http(k, speed)
        wslog("sys", k["id"],
              "карт вернулся стоящим — возвращаю %s, осталось %d с, лимит %d"
              % (phase, rest, speed))

    threading.Thread(target=go, daemon=True).start()


def chunk_len(rest):
    """Сколько секунд просить у платы за один раз.

    Измерено 06.09: прошивка гасит заезд ровно на 600 секундах, какую
    длину ей ни пришли. `lengthDrive` в телеметрии показывает присланное
    число, но считает плата по своему. Патч константы 600000 в дампе
    не помог — значит предел не там.

    Поэтому длинный заезд сервер режет сам: просит у платы кусок не
    длиннее `chunk_seconds` и перед его концом перезапускает.
    """
    lim = S["chunk_seconds"]
    if lim <= 0 or rest <= lim:
        return int(rest)
    # Хвост меньше 30 секунд не оставляем — лучше два куска поровну,
    # чем лишний перезапуск ради полуминуты. Но половина остатка тоже
    # обязана влезать в предел, иначе плата погасит карт раньше, чем
    # придёт продление.
    if rest - lim < 30:
        return int(min(lim, rest / 2 + 1))
    return int(lim)


def ride_renew(kart):
    """Продлить идущий заезд следующим куском, не закрывая его.

    Порядок тот же, что при старте, и по той же причине: разрешение
    движения побочно сбрасывает лимит скорости, поэтому идёт первым.
    Stop в начале обязателен — иначе плата досчитает свой старый кусок
    и погаснет посреди следующего.
    """
    def go():
        r = kart.get("ride") or {}
        if r.get("phase") not in ("ride", "crawl"):
            return
        rest = int(r.get("t_end", 0) - time.time())
        if rest < 5:
            return
        piece = chunk_len(rest)

        k = live_kart(kart)
        ws_send(k, {"Command": "Stop"})
        time.sleep(0.4)
        k = live_kart(kart)
        # Разрешение шлём ВСЕГДА, не глядя на телеметрию. drive_gate()
        # сверяется с последним Status, а он снят ДО нашего Stop и почти
        # всегда показывает kOn=1: запрос не уходил, Stop ронял kOn, и
        # Start без /On6 оставлял карт стоять до конца заезда. Докатка
        # разрешение не возвращает — карт докатывали руками.
        want_set(k, gate=True)
        if kart_online(k) and kart_reachable(k):
            send_gate_now(k, True)
        # Выход 7 здесь НЕ трогаем. Измерено 07.09: прошивка сама поднимает
        # kOn1 по команде Start и роняет по Stop — оба выхода привязаны к
        # состоянию заезда внутри платы. Наш /On7 отсюда прилетал уже посреди
        # докатки (поток продления стартовал раньше неё) и зажигал свет обратно.
        if S["drive_settle"]:
            time.sleep(S["drive_settle"])
        k = live_kart(kart)
        ws_send(k, {"Command": "Start", "Length": piece})
        time.sleep(0.3)

        # Куски покрывают и докатку, значит продление может попасть внутрь
        # неё. Тогда возвращать обычный лимит карта нельзя — скорость
        # прыгнула бы обратно вверх посреди докатки. И выход 7 надо гасить
        # заново: Start его поднимает.
        # Лимит и выход 7 тоже шлём всегда: Start их сбросил, а телеметрия
        # в памяти по-прежнему старая и сказала бы, что всё уже стоит.
        k = live_kart(kart)
        crawl = (k.get("ride") or {}).get("phase") == "crawl"
        speed = S["speed_crawl"] if crawl else kart_speed(k.get("duuid"))
        if crawl:
            want_set(k, light=False)
        if S["speed_http"]:
            want_set(k, speed=speed)
        if kart_online(k) and kart_reachable(k):
            if crawl:
                send_light_now(k, False)
            if S["speed_http"]:
                send_speed_now(live_kart(kart), speed)

        cur = kart.get("ride") or {}
        if cur.get("phase") in ("ride", "crawl"):
            cur["chunk_end"] = time.time() + piece
            cur["chunks"] = cur.get("chunks", 1) + 1
        wslog("sys", k["id"], "продление заезда: кусок %d с, всего осталось %d с"
              % (piece, rest))

    threading.Thread(target=go, daemon=True).start()


def ride_start(kart, minutes, speed_idx, test=False):
    sp = S["speeds"][speed_idx]
    seconds = minutes * 60

    # Порядок здесь выстрадан и важен:
    #   1. разрешение движения /On6 — без него карт не поедет;
    #   2. пауза, чтобы плата дописала свои настройки;
    #   3. Start — он поднимает выходы и сбрасывает состояние платы;
    #   4. и только теперь лимит скорости, по HTTP.
    # Лимит после Start, потому что Start его затирает.
    # Заезд регистрируем ПЕРЕД тем, как пойдут запросы к плате.
    # Разрешение и лимит идут по HTTP и на недоступном карте висят
    # до таймаута — это секунды. Всё это время карт числился бы
    # свободным, и сторож успевал заглушить только что начатый заезд.
    now = time.time()
    kart["ride"] = {"phase": "ride", "minutes": minutes, "speed": speed_idx,
                    "t0": now, "t_paid": now + seconds,
                    "t_end": now + seconds + S["crawl_seconds"],
                    "test": bool(test)}
    kart["drive_since"] = 0
    kart["stuck"] = False
    kart["crawl_tries"] = 0
    kart["crawl_sent"] = 0
    # Кусок планируем на ВЕСЬ заезд вместе с докаткой. Тогда докатке
    # не нужен собственный перезапуск: карт уже едет, ему просто гасят
    # выход 7 и роняют лимит.
    piece = chunk_len(seconds + S["crawl_seconds"])
    ride_event(kart, "start", minutes=minutes, test=bool(test),
               speed=kart_speed(kart.get("duuid")),
               crawl_seconds=S["crawl_seconds"])
    kart["ride"]["chunks"] = 1

    drive_gate(kart, True)      # обычно уже поднято — запрос не уйдёт
    # /On7 не шлём: Start поднимает kOn1 сам. Лишний HTTP к плате не нужен.
    if S["drive_settle"]:
        time.sleep(S["drive_settle"])
    ws_send(kart, {"Command": "Start", "Length": piece})
    # Лимит — ПОСЛЕ Start и по HTTP. Вебсокетный MaxSpeed на этой прошивке
    # телеметрию не двигает (проверено 07.09: MaxSpeed OK, а Speed остаётся 0),
    # HTTP-значение держится. И Start сбрасывает состояние, поэтому он первым.
    time.sleep(0.3)
    set_speed_http(kart, kart_speed(kart.get("duuid")))

    # Отсчёт ведём от момента, когда Start реально ушёл в карт, иначе
    # таймер в панели убежит вперёд на всё время ожидания HTTP.
    now = time.time()
    kart["ride"].update({"t0": now, "t_paid": now + seconds,
                         "t_end": now + seconds + S["crawl_seconds"],
                         "chunk_end": now + piece})
    # Докатка у тест-драйва такая же: она нужна, чтобы человек не встал
    # посреди трассы, а это не зависит от того, платный заезд или пробный.
    wslog("sys", kart["id"], "%s %d мин, скорость «%s» (%d)%s"
          % ("ТЕСТ-ДРАЙВ" if test else "заезд", minutes,
             "лимит", kart_speed(kart.get("duuid")),
             "" if piece >= seconds
             else ", кусками по %d с (предел платы)" % piece))


def crawl_kick(kart, again=False):
    """Начать докатку: погасить выход 7 и уронить лимит скорости.

    Карт при этом НЕ останавливается. Куски заезда планируются сразу на
    оплаченное время плюс докатку, поэтому плата уже едет и перезапускать
    её незачем.

    Раньше здесь был полный цикл Stop → On6 → MaxSpeed → Start. На парке
    из тринадцати картов эти циклы выстраивались в очередь через общий
    HTTP-шлюз и занимали до тридцати секунд — маршал видел это как
    «карты встали».
    """
    def go():
        k = live_kart(kart)
        if (k.get("ride") or {}).get("phase") != "crawl":
            return
        speed = S["speed_crawl"]
        speed_gate(k, False)              # подсветка гаснет
        k = live_kart(kart)
        set_speed_http(k, speed)          # и лимит падает до докаточного
        cur = k.get("ride") or {}
        cur["crawl_sent"] = time.time()
        wslog("sys", k["id"], "докатка: выход 7 снят, лимит %d" % speed)

    threading.Thread(target=go, daemon=True).start()

def ride_crawl(kart):
    r = kart.get("ride") or dict(IDLE)
    r["phase"] = "crawl"
    r["t_end"] = time.time() + S["crawl_seconds"]
    kart["ride"] = r
    r["crawl_tries"] = 0
    r["crawl_sent"] = time.time()
    crawl_kick(kart)


# Журнал заездов для внешних систем. Кольцо на 500 записей: CRM забирает
# события по /api/v1/events?since=..., а если она полежала — не страшно,
# в панели и логе всё то же самое.
ride_events = []
events_lock = threading.Lock()
EVENTS_MAX = 500


def ride_event(kart, kind, **extra):
    e = {"at": time.time(), "event": kind,
         "duuid": str(kart.get("duuid") or ""),
         "number": KART_NAMES.get(str(kart.get("duuid") or ""), "")}
    e.update(extra)
    with events_lock:
        ride_events.append(e)
        del ride_events[:-EVENTS_MAX]


def ride_finish(kart, why="заезд закончен"):
    """Закрыть заезд: погасить карт, снять разрешение, забыть слепок.

    Карт гасит себя сам по своему таймеру, но Stop шлём всё равно: если
    его таймер не сработал, машина не должна остаться на ходу. И слепок
    обязательно выбрасываем — иначе законченный заезд оживёт при
    следующем подключении.
    """
    r0 = kart.get("ride") or {}
    # Останавливает ТОЛЬКО снятие разрешения движения. Лимит нулём этого
    # не делает: 10.09 замерено, что при kOn=1 карт продолжает ехать самым
    # малым газом, даже когда driveOn=0. Поэтому здесь Off6 — и он уходит
    # в желаемое состояние, так что не дошедший запрос дошлётся сам.
    ws_send(kart, {"Command": "Stop"})
    drive_gate(kart, False)
    speed_gate(kart, True)
    ride_event(kart, "finish", why=why,
               minutes=r0.get("minutes", 0), test=bool(r0.get("test")),
               started=r0.get("t0", 0))
    kart["ride"] = dict(IDLE)
    kart["ride_ended"] = time.time()
    kart["drive_since"] = 0
    ghost_drop(kart.get("duuid"))
    wslog("sys", kart["id"], why)


def ride_stop(kart):
    ride_finish(kart, "остановлен вручную")


def ride_ticker():
    while True:
        time.sleep(1.0)
        now = time.time()

        # Слепки не копим вечно: карт, который не возвращается и не едет,
        # через GHOST_TTL уходит из панели совсем.
        with karts_lock:
            for duuid, g in list(ghosts.items()):
                if duuid in karts:
                    continue
                if (now - g.get("gone", 0) > GHOST_TTL
                        and not ride_alive(g.get("ride"), now)):
                    ghosts.pop(duuid, None)

        for kart in all_karts():
            r = kart.get("ride") or dict(IDLE)
            phase = r.get("phase", "idle")

            # Продлеваем только если кусок реально кончается РАНЬШЕ
            # оплаченного времени. Иначе сервер делал полный цикл
            # Stop → On6 → MaxSpeed → Start ради последних секунд: карт
            # вставал прямо перед докаткой, а смысла в этом ноль.
            # 07.09 так ушло продление «кусок 5 с, всего осталось 5 с».
            if (phase in ("ride", "crawl") and S["chunk_seconds"] > 0
                    and r.get("chunk_end")
                    and r["chunk_end"] < r.get("t_end", 0) - 30
                    and now >= r["chunk_end"] - S["chunk_lead"]
                    and now - r.get("renew_at", 0) > 10):
                r["renew_at"] = now
                ride_renew(kart)

            if phase == "ride" and now >= r.get("t_paid", 0):
                if S["crawl_seconds"] > 0:
                    ride_crawl(kart)
                else:
                    # Докатка выключена — значит оплаченное время и есть
                    # весь заезд. Раньше здесь заезд просто стирался: без
                    # Stop, без снятия разрешения, без выброса слепка.
                    ride_finish(kart)

            elif phase == "crawl":
                if now >= r.get("t_end", 0):
                    ride_finish(kart)
                else:
                    # Сторож докатки. Карт в этой фазе обязан ехать. Если он
                    # стоит — команда не дошла или не подействовала, и надо
                    # повторить весь набор, а не ждать у моря погоды.
                    # Два повтора; дальше только запись в лог — значит дело
                    # не в порядке команд, а в самой плате.
                    st = kart.get("status") or {}
                    fresh = now - kart.get("status_at", 0) < S["status_period"] * 2 + 5
                    if (fresh
                            and str(st.get("driveOn", "0")) != "1"
                            and now - r.get("crawl_sent", 0) > 8
                            and r.get("t_end", 0) - now > 6
                            and r.get("crawl_tries", 0) < 2):
                        r["crawl_tries"] = r.get("crawl_tries", 0) + 1
                        r["crawl_sent"] = now
                        wslog("sys", kart["id"],
                              "докатка: карт стоит, повторяю набор команд")
                        crawl_kick(kart, again=True)

            elif phase == "idle":
                # Сторож: карт числится свободным, а в телеметрии driveOn=1.
                #
                # Срабатывает, только если так продержалось 10 секунд подряд.
                # Раньше здесь было `now - stuck_since > 10`, а stuck_since у
                # нового карта равен нулю — то есть условие выполнялось сразу,
                # и Stop уходил в первый же тик. На слабом сигнале карт успевал
                # переподключиться между стартом и опросом, сервер на мгновение
                # считал его свободным — и сторож глушил живой заезд через
                # секунду после старта. Отсюда «driveOn=1, потом сразу 0».
                st = kart.get("status") or {}

                # Сторож смотрит на kOn, а не на driveOn: именно поднятое
                # разрешение движения означает, что карт может поехать.
                # driveOn при этом бывает нулём, а карт всё равно едет.
                if str(st.get("kOn", "0")) == "1":
                    first = kart.get("drive_since") or now
                    kart["drive_since"] = first
                    held = now - first
                    # Не трогаем карт сразу после его же заезда: докатка
                    # и хвост телеметрии не должны выглядеть как ЧП.
                    # И не судим тот, что только что подключился: про его
                    # состояние мы ещё ничего толком не знаем.
                    calm = (now - kart.get("ride_ended", 0) > 15 and
                            now - kart.get("connected", 0) > 20)
                    if held > 10 and calm:
                        kart["stuck"] = True
                        # Stop отсюда НЕ шлём. Сторож судит по собственному
                        # незнанию: после перезапуска сервера состояния заездов
                        # нет вообще, все карты возвращаются едущими — и Stop
                        # ушёл бы на весь парк разом, под клиентами. Решение
                        # об остановке машины с человеком принимает маршал,
                        # а наше дело — показать ему красную плашку.
                        if now - kart.get("stuck_logged", 0) > 30:
                            kart["stuck_logged"] = now
                            wslog("sys", kart["id"],
                                  "ВНИМАНИЕ: driveOn=1 вне заезда уже %d с — "
                                  "проверь карт, автоматический Stop отключён"
                                  % int(held))
                else:
                    kart["drive_since"] = 0
                    kart["stuck"] = False


def status_poller():
    """Телеметрия по вебсокету.

    Спрашиваем по одному карту и размазываем опрос ровно по всему периоду:
    ESP8266 не любит пачки, а пятнадцать запросов подряд — это именно пачка.
    При status_period = 6 и пятнадцати картах между двумя запросами выходит
    почти полсекунды, и в эфире всё время тихо.
    """
    while True:
        ks = all_karts()
        if not ks:
            time.sleep(1.0)
            continue
        gap = max(0.2, float(S["status_period"]) / len(ks))
        for kart in ks:
            ws_send(kart, {"Command": "Status"})
            time.sleep(gap)


# ======================================================================== вход

sessions = {}
SESSION_TTL = 12 * 3600


def session_new(role):
    tok = secrets.token_urlsafe(24)
    sessions[tok] = {"role": role, "exp": time.time() + SESSION_TTL}
    return tok


def session_role(tok):
    s = sessions.get(tok or "")
    if not s:
        return None
    if s["exp"] < time.time():
        sessions.pop(tok, None)
        return None
    return s["role"]


def check(a, b):
    # Сравниваем байты, а не строки. hmac.compare_digest на str умеет только
    # ASCII и падает с TypeError, если в пароле или в раскладке клавиатуры
    # попалась кириллица. Кодирование в UTF-8 снимает ограничение и сохраняет
    # постоянное время сравнения.
    try:
        return hmac.compare_digest(str(a or "").encode("utf-8"),
                                   str(b or "").encode("utf-8"))
    except (UnicodeError, TypeError):
        return False


MARSHAL_OPEN = not cstr("marshal_pass", "").strip()


# ======================================================================= сервер

PANEL = os.path.join(HERE, "panel.html")
ADMIN = os.path.join(HERE, "admin.html")
HTTP_TIMEOUT = 8.0

# Раньше здесь был ОДИН лок на все платы сразу. С одним картом это было
# незаметно, а на двенадцати превратилось в очередь: каждый недоступный
# карт держит лок все свои три секунды таймаута, и старт заезда ждал,
# пока отстоятся чужие таймауты. Теперь лок свой на каждый адрес, а
# общий предохранитель — семафор, чтобы не открывать сто сокетов разом.
kart_http_locks = {}
kart_http_locks_guard = threading.Lock()

# Раньше здесь стоял Semaphore(6): до шести плат получали HTTP одновременно.
# На ESP8266 это дорого — обработка HTTP и обслуживание вебсокета крутятся в
# одном цикле прошивки, и пока плата разбирает запрос, вебсокет не живёт.
# В логе 05.09 из четырнадцати запросов группового старта три не прошли по
# таймауту, и отвалились ровно эти платы. Поэтому теперь строго по одному
# запросу на весь парк и пауза между разными платами: групповой старт
# растягивается на секунды, зато каждая плата получает свой запрос в тишине.
KART_HTTP_GAP = 0.8

# Сколько запросов к РАЗНЫМ платам разрешено одновременно. Настройка
# http_parallel в marshal.conf. По умолчанию 1 — прежнее поведение.
# Больше единицы разгружает очередь, но добавляет одновременных
# передатчиков в эфир: на перегруженной точке доступа это может
# ухудшить связь. Поднимать по одному и смотреть в лог.
kart_http_gate = threading.Semaphore(max(1, min(6, cint("http_parallel", 1))))
kart_http_last = [0.0]


def http_lock_for(ip):
    with kart_http_locks_guard:
        lk = kart_http_locks.get(ip)
        if lk is None:
            lk = kart_http_locks[ip] = threading.Lock()
        return lk


class Handler(BaseHTTPRequestHandler):
    server_version = "SmartKart/2.1"
    protocol_version = "HTTP/1.1"

    def log_message(self, fmt, *args):
        pass

    # -------------------------------------------------------------- служебное
    def role(self):
        tok = ""
        for part in self.headers.get("Cookie", "").split(";"):
            part = part.strip()
            if part.startswith("mk="):
                tok = part[3:]
        return session_role(tok) or ("marshal" if MARSHAL_OPEN else None)

    def need(self, want):
        r = self.role()
        if (want == "admin" and r == "admin") or \
           (want == "marshal" and r in ("admin", "marshal")):
            return True
        self.send_json(403, {"ok": False, "error": "нужен вход"})
        return False

    def body_json(self):
        try:
            n = int(self.headers.get("Content-Length") or 0)
        except ValueError:
            n = 0
        if not n:
            return {}
        try:
            return json.loads(self.rfile.read(n).decode("utf-8"))
        except (ValueError, UnicodeDecodeError):
            return {}

    def send_json(self, code, obj):
        body = json.dumps(obj, ensure_ascii=False).encode("utf-8")
        self.send_response(code)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(body)

    def send_file(self, path):
        try:
            with open(path, "rb") as fh:
                body = fh.read()
        except OSError:
            return self.send_error(500, "нет файла %s" % os.path.basename(path))
        self.send_response(200)
        self.send_header("Content-Type", "text/html; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(body)

    def send_html(self, code, text):
        body = text.encode("utf-8")
        self.send_response(code)
        self.send_header("Content-Type", "text/html; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(body)

    # ------------------------------------------------------------------- GET
    def do_GET(self):
        parsed = urllib.parse.urlsplit(self.path)
        path = parsed.path
        if path.startswith("/api/v1/") and self.do_api(path, "GET"):
            return

        if (self.headers.get("Upgrade", "").lower() == "websocket"
                and self.headers.get("Sec-WebSocket-Key")):
            return self.handle_ws()

        if path in ("/", "/index.html", "/panel.html"):
            if not MARSHAL_OPEN and self.role() is None:
                return self.login_page("")
            return self.send_file(PANEL)

        if path == "/admin":
            if self.role() != "admin":
                return self.login_page("", admin=True)
            return self.send_file(ADMIN)

        if path == "/login":
            return self.login_page("", admin=parsed.query == "admin")

        if path == "/logout":
            self.send_response(302)
            self.send_header("Location", "/")
            self.send_header("Set-Cookie", "mk=; Path=/; Max-Age=0")
            self.send_header("Content-Length", "0")
            self.end_headers()
            return

        if path == "/api/state":
            if not self.need("marshal"):
                return
            return self.send_json(200, api_state(self.role() == "admin"))

        if path == "/api/config":
            if not self.need("marshal"):
                return
            return self.send_json(200, {
                "ok": True, "presets": S["presets"],
                "test_presets": S["test_presets"], "speeds": S["speeds"],
                "speed_crawl": S["speed_crawl"], "crawl_seconds": S["crawl_seconds"],
                "admin": self.role() == "admin", "now": time.time(),
            })

        if path == "/api/admin/settings":
            if not self.need("admin"):
                return
            return self.send_json(200, {
                "ok": True, "presets": S["presets"],
                "test_presets": S["test_presets"], "speeds": S["speeds"],
                "speed_crawl": S["speed_crawl"], "crawl_seconds": S["crawl_seconds"],
                "karts": KART_NAMES,
                "seen": sorted({k.get("duuid") for k in all_karts() if k.get("duuid")}),
                "conf_path": CONF_PATH,
            })

        if path == "/api/admin/log":
            if not self.need("admin"):
                return
            with ws_lock:
                return self.send_json(200, {"ok": True, "log": list(ws_log[-200:])})

        if path == "/api/admin/discover":
            if not self.need("admin"):
                return
            q = urllib.parse.parse_qs(parsed.query)
            return self.send_json(200, discover(
                [s.strip() for s in q.get("subnet", []) if s.strip()]))

        if path == "/health":
            return self.send_json(200, {"ok": True, "karts": len(karts)})

        if path == "/favicon.ico":
            self.send_response(204)
            self.send_header("Content-Length", "0")
            self.end_headers()
            return

        self.send_error(404, "Not found")

    # ------------------------------------------------------------------ POST
    # Всё, что меняет состояние, — только POST. Открытая в браузере ссылка
    # больше не может запустить карт.

    # ================================================================ API v1
    #
    # Внешний интерфейс для CRM и ботов. Отдельный от панели: панель ходит
    # по сессии в куке, внешние системы — по токену в заголовке.
    #
    #     Authorization: Bearer <api_token>
    #     или  X-Api-Token: <api_token>
    #
    # Токен задаётся в marshal.conf строкой api_token. Пустой токен —
    # API выключен целиком, чтобы случайно не открыть парк наружу.
    #
    # Ответ всегда JSON. Успех — {"ok": true, ...}, отказ — {"ok": false,
    # "error": "текст"}. Коды: 200 успех, 400 плохие параметры,
    # 401 нет или неверный токен, 404 карт не найден, 503 API выключен.

    def api_auth(self):
        want = S["api_token"]
        if not want:
            self.send_json(503, {"ok": False,
                                 "error": "внешний API выключен: в marshal.conf "
                                          "нет строки api_token"})
            return False
        got = (self.headers.get("X-Api-Token") or "").strip()
        if not got:
            head = (self.headers.get("Authorization") or "").strip()
            if head.lower().startswith("bearer "):
                got = head[7:].strip()
        try:
            ok = hmac.compare_digest(got.encode("utf-8"), want.encode("utf-8"))
        except Exception:
            ok = False
        if not ok:
            self.send_json(401, {"ok": False, "error": "неверный токен"})
            return False
        return True

    def api_kart(self, key):
        """Карт по DUUID или по номеру на кузове."""
        k = find_kart(str(key or ""))
        if k:
            return k
        key = str(key or "").strip()
        for duuid, name in KART_NAMES.items():
            if str(name).strip() == key:
                return find_kart(duuid)
        return None

    def do_api(self, path, method):
        if not self.api_auth():
            return True

        if path == "/api/v1/karts" and method == "GET":
            now = time.time()
            out = []
            for k in all_karts():
                it = state_item(k, now, False, True)
                out.append({
                    "duuid": it["duuid"],
                    "number": KART_NAMES.get(it["duuid"], ""),
                    "state": it["phase"],          # idle | ride | crawl
                    "online": it["online"],
                    "left": it["left"],            # секунд до конца
                    "minutes": it["minutes"],      # сколько было оплачено
                    "speed": it["maxspeed"],       # лимит в процентах
                    "test": it["test"],
                    "alarm": it["stuck"],
                })
            return self.send_json(200, {"ok": True, "karts": out,
                                        "presets": S["presets"],
                                        "test_presets": S["test_presets"],
                                        "crawl_seconds": S["crawl_seconds"],
                                        "server_time": now}) or True

        if path == "/api/v1/start" and method == "POST":
            d = self.body_json()
            k = self.api_kart(d.get("kart"))
            if not k:
                return self.send_json(404, {"ok": False,
                                            "error": "карт не найден или не на связи"}) or True
            try:
                minutes = int(d.get("minutes"))
            except (TypeError, ValueError):
                return self.send_json(400, {"ok": False, "error": "minutes должно быть числом"}) or True
            test = bool(d.get("test"))
            allowed = S["test_presets"] if test else S["presets"]
            if minutes not in allowed:
                return self.send_json(400, {"ok": False,
                                            "error": "недопустимая длительность, разрешено %s"
                                                     % allowed}) or True
            if (k.get("ride") or {}).get("phase", "idle") != "idle":
                return self.send_json(400, {"ok": False, "error": "карт уже в заезде"}) or True
            if d.get("speed") is not None:
                try:
                    val = max(0, min(100, int(d.get("speed"))))
                except (TypeError, ValueError):
                    return self.send_json(400, {"ok": False, "error": "speed 0..100"}) or True
                KART_SPEED[str(k.get("duuid"))] = val
                try:
                    write_names(KART_NAMES, KART_SPEED)
                except OSError:
                    pass
            ride_start(k, minutes, 0, test)
            wslog("sys", k["id"], "СRM: старт заезда %d мин" % minutes)
            return self.send_json(200, {"ok": True, "duuid": k.get("duuid"),
                                        "minutes": minutes}) or True

        if path == "/api/v1/stop" and method == "POST":
            d = self.body_json()
            k = self.api_kart(d.get("kart"))
            if not k:
                return self.send_json(404, {"ok": False, "error": "карт не найден"}) or True
            ride_stop(k)
            wslog("sys", k["id"], "СRM: заезд остановлен")
            return self.send_json(200, {"ok": True}) or True

        if path == "/api/v1/speed" and method == "POST":
            d = self.body_json()
            k = self.api_kart(d.get("kart"))
            duuid = str(k.get("duuid")) if k else str(d.get("kart") or "").strip()
            if not duuid:
                return self.send_json(404, {"ok": False, "error": "карт не найден"}) or True
            try:
                val = max(0, min(100, int(d.get("speed"))))
            except (TypeError, ValueError):
                return self.send_json(400, {"ok": False, "error": "speed 0..100"}) or True
            KART_SPEED[duuid] = val
            try:
                write_names(KART_NAMES, KART_SPEED)
            except OSError:
                pass
            if k and (k.get("ride") or {}).get("phase") in ("ride", "crawl"):
                threading.Thread(target=lambda: set_speed_http(live_kart(k), val),
                                 daemon=True).start()
            wslog("sys", duuid, "СRM: лимит скорости %d%%" % val)
            return self.send_json(200, {"ok": True, "speed": val}) or True

        if path == "/api/v1/stopall" and method == "POST":
            n = 0
            for k in all_karts():
                ride_stop(k)
                n += 1
            wslog("sys", "*", "СRM: СТОП ВСЕМ (%d)" % n)
            return self.send_json(200, {"ok": True, "stopped": n}) or True

        if path == "/api/v1/events" and method == "GET":
            # Журнал заездов для CRM: что началось и чем кончилось.
            # since — метка времени, отдаём всё, что позже неё.
            q = urllib.parse.parse_qs(urllib.parse.urlsplit(self.path).query)
            try:
                since = float((q.get("since") or ["0"])[0])
            except ValueError:
                since = 0.0
            with events_lock:
                out = [e for e in ride_events if e["at"] > since]
            return self.send_json(200, {"ok": True, "events": out,
                                        "server_time": time.time()}) or True

        return False

    def do_POST(self):
        path = urllib.parse.urlsplit(self.path).path
        if path.startswith("/api/v1/") and self.do_api(path, "POST"):
            return

        if path == "/login":
            return self.do_login()

        if path == "/api/start":
            if not self.need("marshal"):
                return
            d = self.body_json()
            kart = find_kart(str(d.get("kart", "")))
            if not kart:
                return self.send_json(200, {"ok": False, "error": "карт не на связи"})
            try:
                minutes = int(d.get("minutes"))
                speed = int(d.get("speed", 0))
            except (TypeError, ValueError):
                return self.send_json(200, {"ok": False, "error": "плохие параметры"})
            test = bool(d.get("test"))
            allowed = S["test_presets"] if test else S["presets"]
            if minutes not in allowed:
                return self.send_json(200, {"ok": False, "error": "недопустимая длительность"})
            if not 0 <= speed < len(S["speeds"]):
                return self.send_json(200, {"ok": False, "error": "недопустимая скорость"})
            ride_start(kart, minutes, speed, test)
            return self.send_json(200, {"ok": True})

        if path == "/api/stop":
            if not self.need("marshal"):
                return
            key = str(self.body_json().get("kart", ""))
            kart = find_kart(key)
            if kart:
                ride_stop(kart)
                return self.send_json(200, {"ok": True})
            # Карт мог отвалиться прямо посреди заезда — карточка осталась.
            # «Стоп» на ней обязан хотя бы снять заезд с сервера, иначе
            # вернувшийся карт поедет доигрывать отменённое время.
            with karts_lock:
                gh = ghosts.get(key)
                if gh is not None:
                    gh["ride"] = dict(IDLE)
            if gh is not None:
                wslog("sys", key, "заезд снят вручную, карт не на связи")
                return self.send_json(200, {"ok": True, "offline": True})
            return self.send_json(200, {"ok": False, "error": "карт не на связи"})

        if path == "/api/speed":
            # Ползунок скорости в панели. Значение 0..100 сохраняется
            # в karts.conf на этот карт и применяется сразу, если он едет.
            if not self.need("marshal"):
                return
            d = self.body_json()
            duuid = str(d.get("kart") or "").strip()
            try:
                val = max(0, min(100, int(d.get("value"))))
            except (TypeError, ValueError):
                return self.send_json(400, {"ok": False, "error": "нужно число 0..100"})
            if not duuid:
                return self.send_json(400, {"ok": False, "error": "нет карта"})
            KART_SPEED[duuid] = val
            try:
                write_names(KART_NAMES, KART_SPEED)
            except OSError as e:
                wslog("sys", duuid, "не смог сохранить скорость: %s" % e)
            kart = karts.get(duuid)
            if kart and (kart.get("ride") or {}).get("phase") == "ride":
                threading.Thread(
                    target=lambda: set_speed_http(live_kart(kart), val),
                    daemon=True).start()
            wslog("sys", duuid, "лимит скорости задан: %d" % val)
            return self.send_json(200, {"ok": True, "value": val})

        if path == "/api/stopall":
            if not self.need("marshal"):
                return
            n = 0
            for kart in all_karts():
                ride_stop(kart)
                n += 1
            with karts_lock:
                for gh in ghosts.values():
                    if gh.get("ride", {}).get("phase", "idle") != "idle":
                        gh["ride"] = dict(IDLE)
                        n += 1
            wslog("sys", "*", "СТОП ВСЕМ (%d)" % n)
            return self.send_json(200, {"ok": True, "count": n})

        if path == "/api/admin/settings":
            if not self.need("admin"):
                return
            return self.send_json(200, save_settings(self.body_json()))

        if path == "/api/admin/send":
            if not self.need("admin"):
                return
            d = self.body_json()
            cmd = str(d.get("cmd", ""))
            try:
                json.loads(cmd)
            except ValueError as e:
                return self.send_json(200, {"ok": False, "error": "не JSON: %s" % e})
            to = str(d.get("kart", "")) or "*"
            targets = all_karts() if to == "*" else [k for k in all_karts() if k["id"] == to]
            if not targets:
                return self.send_json(200, {"ok": False, "error": "нет подключённых картов"})
            sent = [k["id"] for k in targets if ws_send(k, cmd)]
            return self.send_json(200, {"ok": bool(sent), "sent": sent})

        if path == "/api/admin/http":
            if not self.need("admin"):
                return
            d = self.body_json()
            return self.send_json(200, kart_http(str(d.get("ip", "")),
                                                 str(d.get("path", ""))))

        self.send_error(404, "Not found")

    # ----------------------------------------------------------------- вход
    def do_login(self):
        data = {}
        try:
            n = int(self.headers.get("Content-Length") or 0)
            raw = self.rfile.read(n).decode("utf-8")
            data = {k: v[0] for k, v in urllib.parse.parse_qs(raw).items()}
        except (ValueError, UnicodeDecodeError):
            pass

        user, pwd = data.get("user", ""), data.get("pass", "")
        want_admin = data.get("admin") == "1"

        role = None
        try:
            if check(user, cstr("admin_user", "admin")) and check(pwd, cstr("admin_pass")):
                role = "admin"
            elif not want_admin and not MARSHAL_OPEN and check(pwd, cstr("marshal_pass")):
                role = "marshal"
        except Exception as e:
            # Что бы ни пришло из формы, страница входа должна ответить,
            # а не оборвать соединение стектрейсом.
            wslog("sys", "*", "ошибка проверки пароля: %s" % e)
            role = None

        if not role:
            time.sleep(1.0)
            return self.login_page("Неверный логин или пароль", admin=want_admin)

        tok = session_new(role)
        self.send_response(302)
        self.send_header("Location", "/admin" if role == "admin" else "/")
        self.send_header("Set-Cookie",
                         "mk=%s; Path=/; HttpOnly; SameSite=Lax; Max-Age=%d"
                         % (tok, SESSION_TTL))
        self.send_header("Content-Length", "0")
        self.end_headers()

    def login_page(self, err, admin=False):
        self.send_html(200, LOGIN_HTML
                       .replace("{{ERR}}", html.escape(err))
                       .replace("{{ERRHIDE}}", "" if err else "hidden")
                       .replace("{{ADMIN}}", "1" if admin else "0")
                       .replace("{{TITLE}}", "Админ-панель" if admin else "Панель маршала")
                       .replace("{{USERHIDE}}", "" if admin else "hidden"))

    # ------------------------------------------------------------------- ws
    def handle_ws(self):
        key = self.headers.get("Sec-WebSocket-Key", "")
        addr = "%s:%d" % self.client_address[:2]
        kart_key = self.client_address[0]

        self.wfile.write((
            "HTTP/1.1 101 Switching Protocols\r\n"
            "Upgrade: websocket\r\nConnection: Upgrade\r\n"
            "Sec-WebSocket-Accept: %s\r\n\r\n" % ws_accept_key(key)).encode())
        self.wfile.flush()
        self.close_connection = True

        kart = {"id": kart_key, "addr": addr, "wfile": self.wfile,
                "lock": threading.Lock(), "status": {}, "duuid": "", "name": "",
                "seen": time.time(), "connected": time.time(), "ride": dict(IDLE)}
        with karts_lock:
            karts[kart_key] = kart
        wslog("sys", kart_key, "карт подключился (%s)" % addr)
        ws_send(kart, {"Command": "Status"})

        try:
            while True:
                frame = ws_read_frame(self.rfile)
                if frame is None:
                    break
                opcode, data = frame
                kart["seen"] = time.time()

                if opcode == 0x8:
                    try:
                        ws_write_frame(self.wfile, 0x8)
                    except OSError:
                        pass
                    break
                if opcode == 0x9:
                    with kart["lock"]:
                        ws_write_frame(self.wfile, 0xA, data)
                    continue
                if opcode == 0xA or opcode not in (0x1, 0x2):
                    continue

                text = data.decode("utf-8", "replace")
                try:
                    obj = json.loads(text)
                except ValueError:
                    wslog("in", kart["id"], text)
                    continue
                if not isinstance(obj, dict):
                    wslog("in", kart["id"], text)
                    continue
                wslog("in", kart["id"], status_brief(obj) or text)

                duuid = str(obj.get("DUUID") or "")
                if duuid and duuid != kart["duuid"]:
                    # Опознали карт — перевешиваем его с IP на DUUID:
                    # адрес после перезагрузки меняется, DUUID нет.
                    restored = False
                    with karts_lock:
                        karts.pop(kart["id"], None)
                        gh = ghosts.pop(duuid, None)
                        prev = karts.get(duuid)
                        if prev is not None and prev is not kart:
                            # Карт успел подключиться заново раньше, чем
                            # сервер заметил разрыв старого сокета.
                            kart["ride"] = prev.get("ride", kart["ride"])
                            kart["status"] = kart["status"] or prev.get("status") or {}
                        elif gh is not None:
                            # Старое соединение уже закрылось и оставило слепок.
                            # Телеметрию берём всегда — с ней карточка не
                            # мигает пустотой; заезд только если он ещё идёт.
                            kart["status"] = kart["status"] or gh.get("status") or {}
                            if ride_alive(gh.get("ride")):
                                kart["ride"] = gh["ride"]
                                restored = True
                        kart["duuid"] = duuid
                        kart["id"] = duuid
                        kart["name"] = KART_NAMES.get(duuid, "")
                        karts[duuid] = kart
                    # Плата вернулась — снимаем отставку немедленно, не дожидаясь
                    # истечения паузы: раз вебсокет поднялся, HTTP тоже дойдёт.
                    kart_back(duuid)
                    wslog("sys", duuid, "опознан, имя: %s" % (kart["name"] or "—"))
                    # Свободный карт должен быть вооружён и остановлен.
                    # Если он уже такой — ни одного запроса не уйдёт,
                    # желаемое подтвердится первой же телеметрией.
                    if (kart.get("ride") or {}).get("phase", "idle") == "idle":
                        # Свободный карт обязан быть РАЗОРУЖЕН.
                        # Измерено 10.09: при kOn=1 карт едет с последним
                        # лимитом, даже если driveOn=0 и maxSpeed=0 — ноль
                        # даёт не остановку, а самый малый газ. Значит
                        # единственный настоящий тормоз это снятие
                        # разрешения движения, и держать его поднятым на
                        # свободном карте нельзя: сядет кто угодно и поедет.
                        drive_gate(kart, False)
                        speed_gate(kart, True)
                    # Долг по остановке важнее всего остального: если заезд
                    # кончился, пока плата молчала, снимаем разрешение сразу.
                    # Отложенный СТОП больше не нужен отдельным механизмом:
                    # его роль выполняет реестр желаемого состояния — он и
                    # так досылает всё, что не дошло, включая снятие
                    # разрешения движения.
                    if restored:
                        wslog("sys", duuid, "заезд восстановлен после обрыва связи")
                    # Карт вернулся посреди заезда — вернуть ему заезд.
                    ride_resume(kart)

                if len(obj) > 3:
                    kart["status"] = obj
                    want_done(kart)
                    kart["status_at"] = time.time()
                    ride_watch(kart, obj)
        except (OSError, ValueError):
            pass
        finally:
            with karts_lock:
                # Слепок снимаем до того, как карт исчезнет из реестра, —
                # иначе панель на секунду увидит пустое место.
                #
                # Но только если это соединение всё ещё и есть карт. Мёртвый
                # сокет иногда закрывается через несколько секунд после того,
                # как карт уже подключился заново, и его объект всё это время
                # держит заезд, который на живом карте давно кончился. Такой
                # запоздалый слепок воскрешал докатку с нулём на табло.
                if kart.get("duuid") and karts.get(kart["duuid"]) is kart:
                    ghosts[kart["duuid"]] = {
                        "id": kart["duuid"], "duuid": kart["duuid"],
                        "name": kart.get("name") or "",
                        "addr": kart.get("addr", ""),
                        "ride": kart.get("ride") or dict(IDLE),
                        "status": kart.get("status") or {},
                        "seen": kart.get("seen", time.time()),
                        "gone": time.time(),
                    }
                if karts.get(kart["id"]) is kart:
                    karts.pop(kart["id"], None)
            wslog("sys", kart["id"], "карт отключился")


# ==================================================================== состояние

def state_item(k, now, with_status, online):
    r = k.get("ride") or dict(IDLE)
    phase = r.get("phase", "idle")
    target = r.get("t_end", 0) if phase == "crawl" else r.get("t_paid", 0)
    sp = r.get("speed", 0)
    st = k.get("status") or {}
    item = {
        "id": k.get("id") or k.get("duuid", ""),
        "duuid": k.get("duuid", ""),
        "name": k.get("name") or k.get("duuid") or k.get("id", ""),
        "addr": k.get("addr", ""),
        "idle": round(now - k.get("seen", now), 1),
        "phase": phase,
        "left": max(0, int(target - now)) if phase != "idle" else 0,
        "minutes": r.get("minutes", 0),
        "speed_name": S["speeds"][sp]["name"] if sp < len(S["speeds"]) else "",
        "t0": r.get("t0", 0), "t_paid": r.get("t_paid", 0), "t_end": r.get("t_end", 0),
        "test": bool(r.get("test")),
        "driveOn": st.get("driveOn"), "stuck": bool(k.get("stuck")),
        "online": bool(online) and (now - k.get("seen", 0)) < 20,
        "gone": round(now - k["gone"], 1) if k.get("gone") else 0,
        "maxspeed": kart_speed(k.get("duuid")),
    }
    if with_status:
        item["status"] = st
    return item


def api_state(with_status):
    now = time.time()
    items, live = [], set()

    for k in all_karts():
        # Карт, который ещё не назвал DUUID, лежит в реестре под своим IP
        # и через секунду сменит ключ и имя. Такие карточки вспыхивали в
        # панели и пропадали — это и выглядело как «карты появляются и
        # исчезают». Молчащий дольше 15 секунд показываем: это уже не
        # мельтешение, а действительно неопознанный карт.
        if not k.get("duuid") and now - k.get("connected", now) < 15:
            continue
        if k.get("duuid"):
            live.add(k["duuid"])
        items.append(state_item(k, now, with_status, True))

    # Карты без связи. Раньше они исчезали из панели вместе с заездом и
    # возвращались через несколько секунд с другим временем — маршал читал
    # это как враньё таймера. Теперь карточка остаётся на месте, помечена
    # «нет связи», и её таймер продолжает идти: заезд-то у карта свой,
    # по Length, и он всё это время едет.
    with karts_lock:
        gs = [g for d, g in ghosts.items() if d not in live]
    for g in gs:
        alive = ride_alive(g.get("ride"), now)
        if now - g.get("gone", 0) > GHOST_TTL and not alive:
            continue
        if not alive and g.get("ride", {}).get("phase", "idle") != "idle":
            # Заезд в слепке кончился, пока карта не было. Показывать его
            # как идущий нельзя — это ровно то враньё на табло, из-за
            # которого всё и затевалось.
            g["ride"] = dict(IDLE)
        items.append(state_item(g, now, with_status, False))

    items.sort(key=lambda d: (len(d["name"]), d["name"]))
    return {"ok": True, "karts": items, "now": now}


# ================================================================== настройки

def save_settings(d):
    try:
        presets = [int(x) for x in (d.get("presets") or [])]
        test_presets = [int(x) for x in (d.get("test_presets") or [])]
        speeds = [{"name": str(s.get("name", "")).strip()[:16],
                   "val": int(s.get("val", 0))} for s in (d.get("speeds") or [])]
        # Лимит докатки — проценты, как и ползунок карта. Сервер сам
        # переводит их в шкалу платы 0..255 в set_speed_http.
        crawl_speed = max(0, min(100, int(d.get("speed_crawl", S["speed_crawl"]))))
        crawl_sec = int(d.get("crawl_seconds", S["crawl_seconds"]))
        names = {str(k).strip(): str(v).strip()[:12]
                 for k, v in (d.get("karts") or {}).items() if str(v).strip()}
    except (TypeError, ValueError, AttributeError):
        return {"ok": False, "error": "не разобрал значения"}

    presets = [p for p in presets if 1 <= p <= 180][:6]
    test_presets = [p for p in test_presets if 1 <= p <= 180][:4]
    speeds = [s for s in speeds if s["name"] and 0 <= s["val"] <= 100][:4]
    if not presets:
        return {"ok": False, "error": "нужен хотя бы один пресет времени"}
    if not speeds:
        return {"ok": False, "error": "нужна хотя бы одна градация скорости"}
    if not 0 <= crawl_speed <= 100:
        return {"ok": False, "error": "скорость докатки вне 0..100"}
    if not 0 <= crawl_sec <= 3600:
        return {"ok": False, "error": "окно докатки вне 0..3600 с"}
    if any(not k.isdigit() for k in names):
        return {"ok": False, "error": "DUUID должен быть числом"}

    try:
        write_conf(presets, test_presets, speeds, crawl_speed, crawl_sec, names)
    except OSError as e:
        return {"ok": False, "error": "не смог записать marshal.conf: %s" % e}

    S["presets"] = sorted(presets)
    S["test_presets"] = sorted(test_presets)
    S["speeds"] = speeds
    S["speed_crawl"] = crawl_speed
    S["crawl_seconds"] = crawl_sec
    KART_NAMES.clear()
    KART_NAMES.update(names)
    for k in all_karts():
        if k.get("duuid"):
            k["name"] = KART_NAMES.get(k["duuid"], "")
    wslog("sys", "*", "настройки изменены из админки")
    return {"ok": True, "presets": S["presets"],
            "test_presets": S["test_presets"], "speeds": S["speeds"],
            "speed_crawl": S["speed_crawl"], "crawl_seconds": S["crawl_seconds"],
            "karts": KART_NAMES}


# ============================================================ HTTP к плате

def kart_http(ip, path, timeout=None):
    if not ip:
        return {"ok": False, "error": "не указан IP карта"}
    url = "http://%s/%s" % (ip, path.lstrip("/"))
    headers = {"User-Agent": "SmartKart/2.1"}
    u, p = cstr("kart_user"), cstr("kart_pass")
    if u or p:
        headers["Authorization"] = "Basic " + base64.b64encode(
            ("%s:%s" % (u, p)).encode()).decode("ascii")
    t0 = time.time()
    req = urllib.request.Request(url, headers=headers)
    with kart_http_gate, http_lock_for(ip):  # по одному запросу на весь парк
        gap = KART_HTTP_GAP - (time.time() - kart_http_last[0])
        if gap > 0:
            time.sleep(gap)
        try:
            with NO_PROXY.open(req, timeout=timeout or HTTP_TIMEOUT) as resp:
                raw, status = resp.read(), resp.status
        except urllib.error.HTTPError as e:
            raw, status = e.read(), e.code
        except (urllib.error.URLError, socket.timeout, OSError) as e:
            return {"ok": False, "url": url,
                    "error": str(getattr(e, "reason", e)) or e.__class__.__name__,
                    "ms": int((time.time() - t0) * 1000)}
        finally:
            kart_http_last[0] = time.time()
    try:
        text = raw.decode("utf-8")
    except UnicodeDecodeError:
        text = raw.decode("latin-1", "replace")
    return {"ok": 200 <= status < 400, "url": url, "status": status,
            "ms": int((time.time() - t0) * 1000), "body": text[:20000]}


# ======================================================================= поиск

KART_MARKERS = ("maxSpeed", "ssidAP", "SSDP", "Kart", "kart")


def ssdp_search(timeout=2.5):
    msg = ("M-SEARCH * HTTP/1.1\r\nHOST: 239.255.255.250:1900\r\n"
           'MAN: "ssdp:discover"\r\nMX: 2\r\nST: upnp:rootdevice\r\n\r\n').encode()
    found = {}
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 2)
        s.settimeout(timeout)
        s.sendto(msg, ("239.255.255.250", 1900))
        end = time.time() + timeout
        while time.time() < end:
            try:
                data, addr = s.recvfrom(2048)
            except (socket.timeout, OSError):
                break
            found.setdefault(addr[0], True)
        s.close()
    except OSError:
        pass
    return found


def http_probe(ip):
    try:
        socket.create_connection((ip, 80), 0.35).close()
    except OSError:
        return None
    info = {"ip": ip, "kart": False, "name": "", "detail": ""}
    try:
        req = urllib.request.Request("http://%s/config.live.json" % ip,
                                     headers={"User-Agent": "SmartKart/2.1"})
        with NO_PROXY.open(req, timeout=1.5) as r:
            body = r.read(4096).decode("utf-8", "replace")
    except Exception:
        return info
    if any(m in body for m in KART_MARKERS):
        info["kart"] = True
        info["detail"] = body.replace("\n", " ")[:200]
        try:
            info["name"] = str(json.loads(body).get("SSDP") or "")
        except ValueError:
            pass
    return info


def local_ips():
    ips = set()
    for probe in ("8.8.8.8", "192.168.1.255", "192.168.137.255"):
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            s.connect((probe, 80))
            ips.add(s.getsockname()[0])
            s.close()
        except OSError:
            pass
    try:
        for info in socket.getaddrinfo(socket.gethostname(), None, socket.AF_INET):
            ips.add(info[4][0])
    except OSError:
        pass
    return sorted(i for i in ips
                  if not i.startswith("127.") and not i.startswith("169.254."))


def discover(extra=None):
    import concurrent.futures as cf
    results = {}
    for ip in ssdp_search():
        results[ip] = {"ip": ip, "kart": True, "name": "",
                       "detail": "найден по SSDP", "via": "ssdp"}
    mine = local_ips()
    bases = []
    for my in mine:
        base = ".".join(my.split(".")[:3])
        if base not in bases:
            bases.append(base)
    for base in (extra or []):
        base = base.rstrip(".")
        if base.count(".") == 3:
            base = ".".join(base.split(".")[:3])
        if base.count(".") == 2 and base not in bases:
            bases.append(base)
    targets = ["%s.%d" % (b, i) for b in bases for i in range(1, 255)
               if "%s.%d" % (b, i) not in mine]
    if targets:
        with cf.ThreadPoolExecutor(max_workers=96) as pool:
            for info in pool.map(http_probe, targets):
                if not info:
                    continue
                if info["ip"] in results:
                    results[info["ip"]].update({k: v for k, v in info.items() if v})
                else:
                    info["via"] = "scan"
                    results[info["ip"]] = info
    items = sorted(results.values(), key=lambda d: (not d.get("kart"), d["ip"]))
    return {"ok": True, "subnets": bases, "found": items[:60], "total": len(items)}


# ================================================================ страница входа

LOGIN_HTML = """<!DOCTYPE html>
<html lang="ru"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>{{TITLE}} — вход</title>
<style>
  :root { color-scheme: light dark; }
  body { margin:0; min-height:100vh; display:grid; place-items:center;
         background:#f4f5f7; color:#14181d;
         font:16px/1.5 -apple-system,"Segoe UI",Roboto,Arial,sans-serif; }
  @media (prefers-color-scheme: dark){ body{ background:#111519; color:#dee4eb; } }
  form { background:#fff; border:1px solid #d6dbe2; border-radius:10px;
         padding:28px 30px; width:min(360px,92vw);
         display:flex; flex-direction:column; gap:12px; }
  @media (prefers-color-scheme: dark){ form{ background:#191e25; border-color:#2d3641; } }
  h1 { margin:0 0 4px; font-size:20px; letter-spacing:-0.01em; }
  p.sub { margin:0 0 8px; color:#5a646f; font-size:13.5px; }
  input { font:inherit; padding:10px 12px; border-radius:8px;
          border:1px solid #c3c9d2; background:transparent; color:inherit; }
  button { font:inherit; font-weight:600; padding:11px 16px; border-radius:8px;
           border:0; background:#1f6feb; color:#fff; cursor:pointer; }
  .err { color:#b3261e; font-size:13.5px; margin:0; }
  @media (prefers-color-scheme: dark){ .err{ color:#e2796a; } }
</style></head><body>
<form method="post" action="/login">
  <h1>{{TITLE}}</h1>
  <p class="sub">SmartKart</p>
  <p class="err" {{ERRHIDE}}>{{ERR}}</p>
  <input type="hidden" name="admin" value="{{ADMIN}}">
  <input type="text" name="user" placeholder="логин" autocomplete="username" {{USERHIDE}}>
  <input type="password" name="pass" placeholder="пароль" autocomplete="current-password" autofocus>
  <button type="submit">Войти</button>
</form>
</body></html>"""


# ======================================================================== запуск

def main():
    start_file_log()
    port, host = cint("port", 8080), cstr("host", "0.0.0.0")
    threading.Thread(target=ride_ticker, daemon=True).start()
    threading.Thread(target=want_loop, daemon=True).start()
    threading.Thread(target=status_poller, daemon=True).start()

    srv = ThreadingHTTPServer((host, port), Handler)
    line = "=" * 60
    print(line)
    print("  SMARTKART — сервер картов и панели")
    print(line)
    print("  Панель маршала:  http://localhost:%d/" % port)
    print("  Админ-панель:    http://localhost:%d/admin" % port)
    for ip in local_ips():
        print("  С планшета:      http://%s:%d/" % (ip, port))
    print()
    print("  Настройки и пароль: %s" % CONF_PATH)
    print("  Лог пишется в:      %s" % LOG_DIR)
    print("  Вход в админку:     %s / %s" % (cstr("admin_user", "admin"),
                                             "*" * len(cstr("admin_pass"))))
    print("  Панель маршала:     %s" % ("без пароля" if MARSHAL_OPEN else "по паролю"))
    print()
    print("  Время:    %s мин" % "/".join(str(p) for p in S["presets"]))
    print("  Тест-драйв: %s мин" % "/".join(str(p) for p in S["test_presets"]))
    print("  Скорости: %s" % " · ".join("%s %d" % (s["name"], s["val"])
                                        for s in S["speeds"]))
    print("  Докатка:  %s" % ("%d с на лимите %d, режим %s"
                              % (S["crawl_seconds"], S["speed_crawl"], S["crawl_mode"])
                              if S["crawl_seconds"] else "выключена"))
    print("  Опрос телеметрии: раз в %d с, карты по очереди" % S["status_period"])
    print("  Карт без связи остаётся в панели %d мин, его таймер идёт дальше."
          % (GHOST_TTL // 60))
    if S["drive_on"]:
        print("  Разрешение движения: /%s при старте, %s"
              % (S["drive_on"],
                 ("/%s по окончании" % S["drive_off"]) if S["drive_off"]
                 else "по окончании HTTP не шлём — гасит Stop по вебсокету"))
        if S["speed_fast"] or S["speed_slow"]:
            print("  Скорость выходом 7: /%s заезд, /%s докатка"
                  % (S["speed_fast"] or "—", S["speed_slow"] or "—"))
        if KART_HTTP:
            for duuid in sorted(KART_HTTP):
                print("     HTTP к карту %s → %s" % (duuid, KART_HTTP[duuid]))
        else:
            print("     ! строк http.<DUUID> в конфиге нет — сервер будет"
                  " стучаться по адресу из телеметрии карта")
    print()
    print("  Карты подключаются сюда сами, на этот же порт %d." % port)
    print("  Остановить — Ctrl+C")
    print(line)
    try:
        srv.serve_forever()
    except KeyboardInterrupt:
        print("\nОстановлено.")
        srv.server_close()


if __name__ == "__main__":
    main()
