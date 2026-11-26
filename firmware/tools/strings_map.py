"""Printable strings of the app image with their runtime addresses (tab-separated)."""
import re
import sys

APP = [  # (file offset, load address, length) from bin2elf output
    (0x1010, 0x40201010, 0x763C8),   # .irom0.text (code + const data)
    (0x7E9ED, 0x3FFE8000, 0x6C4),    # .data
    (0x7F0B9, 0x3FFE8700, 0x1920),   # .rodata
]

dump = open(sys.argv[1], "rb").read()
out = open(sys.argv[2], "w", encoding="utf-8")
for off, addr, size in APP:
    blob = dump[off:off + size]
    for m in re.finditer(rb"[\t\r\n -~]{4,}", blob):
        text = m.group().decode("ascii").encode("unicode_escape").decode("ascii")
        out.write(f"{addr + m.start():08x}\t{text}\n")
out.close()
