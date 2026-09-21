#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Разбор дампа флеша ESP8266 с платы SmartKart v5.1.

Запуск:
    python analyze_dump.py kart_dump.bin

Рядом с дампом появятся два файла:
    all_strings.txt — все найденные строки с адресами в флеше
    report.txt      — то же, что печатается на экран
"""

import os
import re
import sys

MIN_LEN = 4                # минимальная длина строки, которую считаем осмысленной
SDK_TAIL = 32 * 1024       # последние 32 КБ — системная область SDK (там SSID и пароль)

IP_RE = re.compile(r'\b(?:\d{1,3}\.){3}\d{1,3}\b')
URL_RE = re.compile(r'\b(?:https?|ws|wss|mqtt|tcp)://[^\s"\'<>]{3,}')

KEYWORDS = [
    'mqtt', 'broker', 'topic', 'subscribe', 'publish',
    'ssid', 'pass', 'wifi', 'ap_', 'sta_',
    'token', 'api', 'http', 'get ', 'post ', 'host:',
    'server', 'port', 'socket', 'udp', 'tcp',
    'kart', 'smart', 'speed', 'mode', 'start', 'stop',
    'timer', 'relay', 'race', 'id',
]


def extract_strings(data, min_len=MIN_LEN):
    """Все печатаемые ASCII-строки в виде списка (адрес, текст)."""
    found = []
    buf = bytearray()
    start = 0
    for i, byte in enumerate(data):
        if 32 <= byte < 127:
            if not buf:
                start = i
            buf.append(byte)
        else:
            if len(buf) >= min_len:
                found.append((start, buf.decode('ascii', 'replace')))
            buf = bytearray()
    if len(buf) >= min_len:
        found.append((start, buf.decode('ascii', 'replace')))
    return found


def is_real_ip(text):
    """Отсеивает номера версий вроде 1.2.3.4, оставляет правдоподобные адреса."""
    parts = text.split('.')
    if len(parts) != 4:
        return False
    for part in parts:
        if not part.isdigit() or not 0 <= int(part) <= 255:
            return False
        if len(part) > 1 and part[0] == '0':
            return False
    return text not in ('0.0.0.0', '255.255.255.255')


def main():
    if len(sys.argv) < 2:
        print('Укажи файл дампа:  python analyze_dump.py kart_dump.bin')
        return 1

    path = sys.argv[1]
    if not os.path.isfile(path):
        print('Файл не найден:', path)
        return 1

    with open(path, 'rb') as handle:
        data = handle.read()

    strings = extract_strings(data)
    out_dir = os.path.dirname(os.path.abspath(path))
    lines = []

    def say(text=''):
        lines.append(text)
        print(text)

    say('Файл: %s' % path)
    say('Размер: %d байт (%.1f МБ)' % (len(data), len(data) / 1048576))
    say('Найдено строк: %d' % len(strings))

    # --- IP-адреса ---
    say('\n=== IP-АДРЕСА ===')
    seen_ip = {}
    for addr, text in strings:
        for candidate in IP_RE.findall(text):
            if is_real_ip(candidate) and candidate not in seen_ip:
                seen_ip[candidate] = (addr, text)
    if seen_ip:
        for ip, (addr, text) in sorted(seen_ip.items()):
            say('  %-16s @ 0x%06X   в строке: %s' % (ip, addr, text[:70]))
    else:
        say('  не найдено')

    # --- URL и хосты ---
    say('\n=== URL / ХОСТЫ ===')
    seen_url = set()
    for addr, text in strings:
        for candidate in URL_RE.findall(text):
            if candidate not in seen_url:
                seen_url.add(candidate)
                say('  0x%06X  %s' % (addr, candidate[:100]))
    if not seen_url:
        say('  не найдено')

    # --- системная область SDK: тут обычно лежат SSID и пароль ---
    say('\n=== СИСТЕМНАЯ ОБЛАСТЬ SDK (последние 32 КБ) ===')
    say('    Здесь ESP8266 хранит настройки WiFi. Ищи название сети и пароль.')
    tail_start = max(0, len(data) - SDK_TAIL)
    tail = [(a, t) for a, t in strings if a >= tail_start]
    if tail:
        for addr, text in tail:
            say('  0x%06X  %s' % (addr, text[:90]))
    else:
        say('  строк не найдено')

    # --- по ключевым словам ---
    say('\n=== СТРОКИ ПО КЛЮЧЕВЫМ СЛОВАМ ===')
    hits = []
    for addr, text in strings:
        low = text.lower()
        matched = [word for word in KEYWORDS if word in low]
        if matched:
            hits.append((addr, text, matched))
    if hits:
        for addr, text, matched in hits[:300]:
            say('  0x%06X  [%s]  %s' % (addr, ','.join(matched[:3]), text[:80]))
        if len(hits) > 300:
            say('  ... ещё %d совпадений, смотри all_strings.txt' % (len(hits) - 300))
    else:
        say('  не найдено')

    # --- файлы на диск ---
    all_path = os.path.join(out_dir, 'all_strings.txt')
    with open(all_path, 'w', encoding='utf-8') as handle:
        for addr, text in strings:
            handle.write('0x%06X\t%s\n' % (addr, text))

    report_path = os.path.join(out_dir, 'report.txt')
    with open(report_path, 'w', encoding='utf-8') as handle:
        handle.write('\n'.join(lines))

    print('\nСохранено:')
    print('  ', all_path)
    print('  ', report_path)
    return 0


if __name__ == '__main__':
    try:
        sys.stdout.reconfigure(encoding='utf-8')
    except Exception:
        pass
    sys.exit(main())
