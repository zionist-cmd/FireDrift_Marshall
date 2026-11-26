"""Join fn_constants.tsv with strings.tsv: which strings each function references.

Writes out/fn_strings.tsv (function, string address, text) and prints a per-region summary.
"""
import bisect
import csv
import sys
from collections import defaultdict

base = sys.argv[1]
strings = []
with open(f"{base}/strings.tsv", encoding="utf-8") as fh:
    for line in fh:
        addr, _, text = line.rstrip("\n").partition("\t")
        strings.append((int(addr, 16), text))
strings.sort()
starts = [a for a, _ in strings]


def lookup(value):
    i = bisect.bisect_right(starts, value) - 1
    if i < 0:
        return None
    addr, text = strings[i]
    return (addr, text) if value < addr + max(len(text), 1) else None


refs = defaultdict(set)
with open(f"{base}/out/fn_constants.tsv", encoding="utf-8") as fh:
    for row in csv.DictReader(fh, delimiter="\t"):
        hit = lookup(int(row["value"], 16))
        if hit:
            refs[int(row["function"], 16)].add(hit)

with open(f"{base}/out/fn_strings.tsv", "w", encoding="utf-8") as out:
    for fn in sorted(refs):
        for addr, text in sorted(refs[fn]):
            out.write(f"{fn:08x}\t{addr:08x}\t{text[:120]}\n")

markers = sys.argv[2:]
for fn in sorted(refs):
    texts = [t for _, t in refs[fn]]
    if any(m in t for t in texts for m in markers):
        shown = ", ".join(sorted({t[:28] for t in texts})[:9])
        print(f"{fn:08x}  [{len(texts):3}]  {shown}")
