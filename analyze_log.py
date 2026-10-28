#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Разбор лога marshal.py по картам: кто отваливается, кто перезагружается,
у кого слабый сигнал, у кого не доходит педаль.

Запуск:
    python analyze_log.py                                 все логи из logs/
    python analyze_log.py logs/marshal-2026-10-25_13.log  один час
    python analyze_log.py logs/marshal-2026-10-25_*.log   весь день

Номера картов берёт из karts.conf рядом со скриптом, если он есть, и из
строк «опознан, имя:» в самом логе. Карт из karts.conf, которого в логе нет
вовсе, попадает в список «не видно».

Пороги взяты из здоровых картов по логу 25.10, 13:00-14:00:
    rssi            медиана −52…−63, хуже −75 почти не бывает
    adcIn при kOn=1 педаль отпущена 43-44, в пол 183-192
    adcIn при kOn=0 0 — педаль запитана через плату и без разрешения мертва
    adc0  при kOn=0 43-45 — ЦАП держит «газ отпущен»
    Status          без ответа 0-1% запросов

Нужен только Python 3.7+, никаких pip-пакетов.
"""

import glob
import os
import re
import statistics
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
NAMES_PATH = os.path.join(HERE, "karts.conf")

LINE_RE = re.compile(r'^(\d\d):(\d\d):(\d\d)\.(\d{3})\s+WS (in|out|sys)\s+(\S+)\s+(.*)$')
FILE_RE = re.compile(r'marshal-(\d{4})-(\d\d)-(\d\d)_(\d\d)\.log$')
FIELD_RE = re.compile(r'(\w+)=(\S+)')

RSSI_WEAK = -75          # ниже — связь на грани
CLUSTER_WINDOW = 120     # обрывы у разных картов в пределах стольких секунд
CLUSTER_KARTS = 3        # ...и у стольких картов сразу — это сеть, а не карт
DROPS_MIN = 3            # здоровый карт рвётся сам 0-1 раз в час
DROPS_PER_HOUR = 2
PEDAL_IDLE = 30          # отпущенная педаль при kOn=1 даёт ~44, ниже — провал
PEDAL_FULL = 150         # в пол даёт ~185, если за час ни разу выше — не доходит
DAC_IDLE_MAX = 60        # ЦАП при kOn=0 выше этого — газ без разрешения


def read_names():
    """karts.conf: `<DUUID> = номер`. Строки .speed и .crawl пропускаем."""
    names = {}
    try:
        with open(NAMES_PATH, encoding="utf-8") as fh:
            for line in fh:
                line = line.split("#", 1)[0].strip()
                if "=" not in line:
                    continue
                key, val = (s.strip() for s in line.split("=", 1))
                if key.isdigit() and val:
                    names[key] = val
    except OSError:
        pass
    return names


def file_base(path):
    """Секунды от начала первого дня — чтобы склеить несколько часов подряд."""
    m = FILE_RE.search(os.path.basename(path))
    if not m:
        return None
    return int(m.group(3)) * 86400, m.group(1, 2, 3)


def hms(t):
    t = int(t) % 86400
    return "%02d:%02d:%02d" % (t // 3600, t // 60 % 60, t % 60)


def new_kart():
    return {"out": 0, "lost": 0, "st": [], "disc": [], "fail": 0,
            "giveup": 0, "broken": 0, "pending": None}


def parse(paths, karts, names):
    for path in paths:
        base = file_base(path)
        day = base[0] if base else 0
        with open(path, "rb") as fh:
            for raw in fh:
                line = raw.decode("utf-8", "replace").rstrip("\r\n")
                m = LINE_RE.match(line)
                if not m:
                    continue
                t = day + int(m.group(1)) * 3600 + int(m.group(2)) * 60 \
                    + int(m.group(3)) + int(m.group(4)) / 1000
                way, who, text = m.group(5), m.group(6), m.group(7)
                if not who.isdigit():
                    continue           # IP до Init или «*» — не карт
                k = karts.setdefault(who, new_kart())
                if way == "out":
                    if '"Status"' in text:
                        if k["pending"] is not None:
                            k["lost"] += 1
                        k["pending"] = t
                        k["out"] += 1
                elif way == "in":
                    if text.startswith("Status  "):
                        k["pending"] = None
                        f = dict(FIELD_RE.findall(text))
                        f["_t"] = t
                        k["st"].append(f)
                    elif "�" in text or any(ord(c) < 32 for c in text):
                        k["broken"] += 1       # обрезанный кадр с чужим хвостом
                else:
                    mn = re.search(r"опознан, имя: (\S+)", text)
                    if mn:
                        names.setdefault(who, mn.group(1))
                    if text.startswith("карт отключился"):
                        k["pending"] = None
                        why = text.split("—", 1)[1].split("|")[0].strip() \
                            if "—" in text else ""
                        last = k["st"][-1] if k["st"] else {}
                        k["disc"].append({"t": t, "why": why,
                                          "rssi": to_int(last.get("rssi"))})
                    elif "НЕ ПРОШЛО" in text:
                        k["fail"] += 1
                    elif text.startswith("СДАЮСЬ"):
                        k["giveup"] += 1


def to_int(v, default=None):
    try:
        return int(str(v).split("_")[0])
    except (TypeError, ValueError):
        return default


def clusters(karts):
    """Минуты, когда связь рвалась сразу у нескольких картов."""
    ev = sorted((d["t"], duuid) for duuid, k in karts.items() for d in k["disc"])
    out, i = [], 0
    while i < len(ev):
        j = i
        while j + 1 < len(ev) and ev[j + 1][0] - ev[i][0] <= CLUSTER_WINDOW:
            j += 1
        who = []
        for _, duuid in ev[i:j + 1]:
            if duuid not in who:
                who.append(duuid)
        if len(who) >= CLUSTER_KARTS:
            out.append((ev[i][0], ev[j][0], who))
            i = j + 1
        else:
            i += 1
    return out


def diagnose(k, in_cluster):
    """Список (вес, что не так, что делать). Больше вес — чинить раньше."""
    st = k["st"]
    found = []

    up = [(s["_t"], to_int(s.get("uptime"))) for s in st if "uptime" in s]
    resets = sum(1 for a, b in zip(up, up[1:])
                 if a[1] is not None and b[1] is not None and b[1] < a[1])
    reb = [to_int(s.get("reboots")) for s in st if "reboots" in s]
    reb = [r for r in reb if r is not None]
    grew = (max(reb) - min(reb)) if reb else 0
    if resets or grew:
        found.append((90, "перезагружается сам: сбросов uptime %d, reboots +%d"
                      % (resets, grew),
                      "цикл перезагрузок — дорожки I2C к U3 и питание. USB, "
                      "консоль 74880, смотреть rst cause (montazh §6)"))

    rssi = [to_int(s.get("rssi")) for s in st]
    rssi = [r for r in rssi if r is not None]
    weak = sum(1 for r in rssi if r < RSSI_WEAK)
    if rssi and (statistics.median(rssi) < -70 or weak > len(rssi) * 0.05):
        found.append((70, "слабый сигнал: rssi медиана %d, мин %d, хуже %d — %d из %d"
                      % (statistics.median(rssi), min(rssi), RSSI_WEAK, weak, len(rssi)),
                      "антенна D1 mini: отодвинуть от металла, снять термоклей (§8)"))

    # Обрывы от перезагрузок уже сосчитаны выше, второй раз их не ругаем.
    own = [d for d in k["disc"] if d["t"] not in in_cluster]
    hours = max(1.0, (st[-1]["_t"] - st[0]["_t"]) / 3600) if st else 1.0
    if len(own) > grew and len(own) >= DROPS_MIN and len(own) / hours >= DROPS_PER_HOUR:
        weak_drop = sum(1 for d in own if d["rssi"] is not None and d["rssi"] < RSSI_WEAK)
        why = sorted({d["why"] for d in own if d["why"]})
        found.append((80, "отваливается сам: обрывов не вместе с остальными %d%s%s"
                      % (len(own),
                         ", %d при слабом сигнале" % weak_drop if weak_drop else "",
                         "; причины: " + "; ".join(why) if why else ""),
                      "сначала сигнал: антенна (§8), потом смотреть снова"
                      if weak_drop * 2 >= len(own) else
                      "не перезагрузка и не сигнал — плата рвёт сокет сама: "
                      "пересадить D1 mini, перепрошить (§4, §5)"))

    if k["broken"] >= 2:
        found.append((60, "битые кадры: %d — плата прислала обрезанный статус"
                      % k["broken"],
                      "сбой на стороне платы, следом обычно обрыв. "
                      "Сверить с перезагрузками и rssi этого карта"))

    if k["out"] >= 20 and k["lost"] > k["out"] * 0.05:
        found.append((50, "не отвечает на Status: %d из %d"
                      % (k["lost"], k["out"]),
                      "плата подвисает — смотреть вместе с обрывами и rssi"))

    armed = [to_int(s.get("adcIn")) for s in st if s.get("kOn") == "1"]
    armed = [a for a in armed if a is not None]
    if len(armed) >= 5:
        if max(armed) == 0:
            found.append((100, "педаль не доходит: adcIn=0 все %d статусов при kOn=1"
                          % len(armed),
                          "у живой педали отпущено ~44. Нет питания педали (красный) "
                          "или обрыв сигнала (зелёный) J9 → R1 → нога 3 U3 (§6)"))
        else:
            # Один провал за час бывает и у здоровых — статус попал на щелчок реле.
            dips = sum(1 for a in armed if a < PEDAL_IDLE)
            if dips >= 3 and dips > len(armed) * 0.02:
                found.append((85, "педаль пропадает на ходу: adcIn ниже %d — %d из %d при kOn=1"
                              % (PEDAL_IDLE, dips, len(armed)),
                              "плохой контакт: разъём педали, J9, пайка R1. "
                              "Шевелить провода при живых полях в админке"))
            if len(armed) >= 30 and max(armed) < PEDAL_FULL:
                found.append((40, "педаль не доходит до упора: макс adcIn %d, у здоровых ~185"
                              % max(armed),
                              "датчик педали или её питание просело"))

    idle = [s for s in st if s.get("kOn") == "0"]
    if len(idle) >= 5:
        dac = [to_int(s.get("adc0"), 0) for s in idle]
        hot = sum(1 for a in dac if a > DAC_IDLE_MAX)
        if hot:
            found.append((110, "ГАЗ БЕЗ РАЗРЕШЕНИЯ: adc0 выше %d при kOn=0 — %d раз, макс %d"
                          % (DAC_IDLE_MAX, hot, max(dac)),
                          "у здоровых при kOn=0 ровно ~44. Вывесить колёса, проверить, "
                          "не едет ли разоружённым; провода газа J9/J10 (§6)"))
        live = sum(1 for s in idle if to_int(s.get("adcIn"), 0) > PEDAL_IDLE)
        if live > len(idle) * 0.5:
            found.append((30, "педаль живая без разрешения: adcIn>%d при kOn=0 в %d из %d"
                          % (PEDAL_IDLE, live, len(idle)),
                          "похоже, питание педали идёт мимо реле платы, не как на "
                          "остальных. Пока adc0 держит ~44, газа нет, но прозвонить"))

    if k["giveup"]:
        found.append((65, "сервер сдался %d раз: команда не подтвердилась" % k["giveup"],
                      "плата получает HTTP, но не выполняет — смотреть плату"))
    if k["fail"] >= 3:
        found.append((45, "HTTP не прошло: %d раз" % k["fail"],
                      "плата не отвечает на HTTP — связь или подвисание"))
    return sorted(found, key=lambda x: -x[0])


def sort_key(item):
    """Строки (DUUID, номер) — по номеру на кузове, безымянные в конце."""
    name = item[1]
    return (0, int(name)) if name.isdigit() else (1, name)


def main(argv):
    if len(argv) > 1:
        paths = []
        for a in argv[1:]:
            paths.extend(sorted(glob.glob(a)) or [a])    # cmd.exe маски не раскрывает
    else:
        paths = sorted(glob.glob(os.path.join(HERE, "logs", "marshal-*.log")))
    paths = [p for p in paths if os.path.isfile(p)]
    if not paths:
        print("Логов нет. Укажи файл:  python analyze_log.py logs\\marshal-2026-10-25_13.log")
        return 1

    names = read_names()
    karts = {}
    parse(paths, karts, names)

    first, last = file_base(paths[0]), file_base(paths[-1])
    print("Логи: %s%s, файлов %d" % (
        os.path.basename(paths[0]),
        " … " + os.path.basename(paths[-1]) if len(paths) > 1 else "", len(paths)))
    if first and last and first[1] != last[1]:
        print("  внимание: несколько дней — времена ниже без даты")

    common = clusters(karts)
    in_cluster = set()
    for t0, t1, who in common:
        for duuid in who:
            for d in karts[duuid]["disc"]:
                if t0 <= d["t"] <= t1:
                    in_cluster.add(d["t"])

    rows = sorted(((d, names.get(d, "?")) for d in karts), key=sort_key)
    print()
    print("  №    DUUID      обрывов  перезагр  rssi мед/мин  педаль kOn=1  нет ответа")
    for duuid, name in rows:
        k = karts[duuid]
        st = k["st"]
        rssi = [to_int(s.get("rssi")) for s in st]
        rssi = [r for r in rssi if r is not None]
        reb = [to_int(s.get("reboots")) for s in st]
        reb = [r for r in reb if r is not None]
        armed = [to_int(s.get("adcIn")) for s in st if s.get("kOn") == "1"]
        armed = [a for a in armed if a is not None]
        print("  %-4s %-10s %7d  %8s  %12s  %12s  %5d/%d" % (
            name, duuid, len(k["disc"]),
            "+%d" % (max(reb) - min(reb)) if reb else "—",
            "%d/%d" % (statistics.median(rssi), min(rssi)) if rssi else "—",
            "%d..%d" % (min(armed), max(armed)) if armed else "не ездил",
            k["lost"], k["out"]))

    missing = sorted(((d, n) for d, n in names.items() if d not in karts), key=sort_key)
    if missing:
        print()
        print("НЕ ВИДНО — в karts.conf есть, в логе ни строки:")
        for d, n in missing:
            print("  %-4s %s" % (n, d))
        print("  → montazh §6 «Карт не появляется в панели»: светодиод D1 mini,"
              " arp -a, два IP на один MAC, curl /config.live.json; антенна §8")

    if common:
        print()
        print("ОБЩИЕ ОБРЫВЫ — связь рвалась у %d+ картов разом. Это сеть, а не карты:"
              % CLUSTER_KARTS)
        for t0, t1, who in common:
            print("  %s–%s  картов %d: %s" % (hms(t0), hms(t1), len(who),
                  ", ".join(names.get(d, d) for d in who)))
        print("  → журнал роутера за эти минуты: 802.11k/v, смена канала (server.md)")

    print()
    print("ЧТО ЧИНИТЬ:")
    found = {d: diagnose(karts[d], in_cluster) for d, _ in rows}
    bad = [r for r in rows if found[r[0]]]
    for duuid, name in sorted(bad, key=lambda r: -found[r[0]][0][0]):
        print("  карт %s (DUUID %s)" % (name, duuid))
        for _, what, todo in found[duuid]:
            print("    • %s" % what)
            print("      → %s" % todo)
    if not bad:
        print("  по этому логу у картов на связи всё в норме")

    unknown = [d for d, n in rows if n == "?"]
    if unknown:
        print()
        print("Без номера: %s. Номер — в karts.conf рядом с marshal.py, или"
              " тест-драйвом (montazh §3)." % ", ".join(unknown))
    return 0


if __name__ == "__main__":
    try:
        sys.stdout.reconfigure(encoding="utf-8")
    except Exception:
        pass
    sys.exit(main(sys.argv))
