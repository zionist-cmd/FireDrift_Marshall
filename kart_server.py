#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Подставной WebSocket-сервер для карта SmartKart v5.1.

Карт жёстко подключается к ws://217.149.25.99:8080/ — этот скрипт
притворяется тем сервером, логирует весь обмен и даёт слать команды руками.

Подготовка (терминал от администратора):
    netsh interface ipv4 show interfaces
    netsh interface ipv4 add address name="<адаптер раздачи>" address=217.149.25.99 mask=255.255.255.0

Запуск:
    pip install websockets
    python kart_server.py

Убрать адрес после работы:
    netsh interface ipv4 delete address name="<адаптер раздачи>" address=217.149.25.99

Команды в консоли:
    status              запрос состояния
    start [длина]       старт заезда, по умолчанию 300
    stop                остановка
    speed <0..255>      максимальная скорость
    {"Command":"..."}   любой сырой JSON
    quit                выход
"""

import asyncio
import json
import sys
import threading
from datetime import datetime

try:
    import websockets
except ImportError:
    print('Не установлена библиотека. Выполни:  pip install websockets')
    sys.exit(1)

HOST = '0.0.0.0'
PORT = 8080
LOGFILE = 'kart_session.log'

clients = set()
loop = None


def log(text):
    stamp = datetime.now().strftime('%H:%M:%S.%f')[:-3]
    line = '[%s] %s' % (stamp, text)
    print(line, flush=True)
    try:
        with open(LOGFILE, 'a', encoding='utf-8') as handle:
            handle.write(line + '\n')
    except Exception:
        pass


async def handler(websocket, *_ignored):
    """Обслуживает подключение карта. Лишние аргументы — ради совместимости версий."""
    try:
        peer = '%s:%s' % websocket.remote_address[:2]
    except Exception:
        peer = 'неизвестно'

    clients.add(websocket)
    log('=== КАРТ ПОДКЛЮЧИЛСЯ: %s ===' % peer)

    try:
        request = getattr(websocket, 'request', None)
        if request is not None and getattr(request, 'headers', None):
            for key in ('User-Agent', 'Origin', 'Host'):
                value = request.headers.get(key)
                if value:
                    log('    %s: %s' % (key, value))
    except Exception:
        pass

    try:
        async for message in websocket:
            if isinstance(message, bytes):
                log('<-- [двоичные данные, %d байт] %s' % (len(message), message[:60].hex()))
                continue
            log('<-- %s' % message)
            try:
                data = json.loads(message)
            except (ValueError, TypeError):
                continue
            if isinstance(data, dict) and data.get('Command') == 'Init':
                log('    ^ карт представился, DUUID=%s' % data.get('DUUID'))
    except Exception as error:
        log('ошибка соединения: %s' % error)
    finally:
        clients.discard(websocket)
        log('=== КАРТ ОТКЛЮЧИЛСЯ: %s ===' % peer)


async def broadcast(payload):
    if not clients:
        log('!!! нет подключённых картов, команда не отправлена')
        return
    for websocket in list(clients):
        try:
            await websocket.send(payload)
            log('--> %s' % payload)
        except Exception as error:
            log('не удалось отправить: %s' % error)


def parse_command(line):
    """Превращает короткую запись в JSON. Сырой JSON пропускает как есть."""
    line = line.strip()
    if not line:
        return None
    if line.startswith('{'):
        return line

    parts = line.split()
    name = parts[0].lower()
    arg = parts[1] if len(parts) > 1 else None

    if name == 'status':
        return json.dumps({'Command': 'Status'})
    if name == 'stop':
        return json.dumps({'Command': 'Stop'})
    if name == 'start':
        length = int(arg) if arg and arg.isdigit() else 300
        return json.dumps({'Command': 'Start', 'Length': length})
    if name == 'speed':
        if not arg or not arg.isdigit():
            print('нужно значение: speed 40')
            return None
        return json.dumps({'Command': 'MaxSpeed', 'MaxSpeed': int(arg)})

    print('не понял команду. Есть: status, start, stop, speed, сырой JSON, quit')
    return None


def console():
    """Читает команды с клавиатуры в отдельном потоке."""
    print('\nКоманды: status | start [длина] | stop | speed <0..255> | сырой JSON | quit\n')
    for line in sys.stdin:
        line = line.strip()
        if line.lower() in ('quit', 'exit'):
            log('выход по команде оператора')
            if loop is not None:
                loop.call_soon_threadsafe(loop.stop)
            return
        payload = parse_command(line)
        if payload and loop is not None:
            asyncio.run_coroutine_threadsafe(broadcast(payload), loop)


async def main():
    global loop
    loop = asyncio.get_running_loop()

    threading.Thread(target=console, daemon=True).start()

    log('сервер слушает %s:%d — жду подключения карта' % (HOST, PORT))
    log('карт должен стучаться на ws://217.149.25.99:8080/')
    log('лог пишется в %s' % LOGFILE)

    async with websockets.serve(handler, HOST, PORT, ping_interval=None):
        await asyncio.Future()


if __name__ == '__main__':
    try:
        sys.stdout.reconfigure(encoding='utf-8')
    except Exception:
        pass
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print('\nостановлено')
