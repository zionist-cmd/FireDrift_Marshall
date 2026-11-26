"""ESP8266 Arduino flash dump -> ELF32 (Xtensa) for Ghidra.

The app image at 0x1000 has segments for irom0 (flash-mapped), iram and dram.
NOBITS sections are added for .bss, ROM and peripheral registers so references
to them resolve in Ghidra.
"""
import struct
import sys

APP_OFFSET = 0x1000
EM_XTENSA = 94
DRAM_END = 0x3FFFC000

SHT_PROGBITS, SHT_STRTAB, SHT_NOBITS = 1, 3, 8
SHF_WRITE, SHF_ALLOC, SHF_EXEC = 1, 2, 4


def read_segments(dump):
    magic, count = dump[APP_OFFSET], dump[APP_OFFSET + 1]
    if magic != 0xE9:
        raise ValueError("no 0xE9 app image at 0x1000")
    entry, = struct.unpack_from("<I", dump, APP_OFFSET + 4)
    pos, segments = APP_OFFSET + 8, []
    for _ in range(count):
        addr, size = struct.unpack_from("<II", dump, pos)
        segments.append((addr, dump[pos + 8:pos + 8 + size]))
        pos += 8 + size
    return entry, segments


def merge_adjacent(segments):
    merged = []
    for addr, data in sorted(segments):
        if merged and merged[-1][0] + len(merged[-1][1]) == addr:
            merged[-1] = (merged[-1][0], merged[-1][1] + data)
        else:
            merged.append((addr, data))
    return merged


def section_name(addr):
    if addr >= 0x40200000:
        return ".irom0.text", SHF_ALLOC | SHF_EXEC
    if addr >= 0x40100000:
        return ".iram0.text", SHF_ALLOC | SHF_EXEC
    if addr == 0x3FFE8000:
        return ".data", SHF_ALLOC | SHF_WRITE
    return ".rodata", SHF_ALLOC | SHF_WRITE


def build(dump):
    entry, segments = read_segments(dump)
    progbits = [(*section_name(a), a, d) for a, d in merge_adjacent(segments)]
    dram_top = max(a + len(d) for _, _, a, d in progbits if a < 0x40000000)
    nobits = [
        (".bss", SHF_ALLOC | SHF_WRITE, dram_top, DRAM_END - dram_top),
        (".rom", SHF_ALLOC | SHF_EXEC, 0x40000000, 0x10000),
        (".dport", SHF_ALLOC | SHF_WRITE, 0x3FF00000, 0x100),
        (".io", SHF_ALLOC | SHF_WRITE, 0x60000000, 0x1000),
    ]
    names = [s[0] for s in progbits] + [s[0] for s in nobits] + [".shstrtab"]
    shstr = b"\0" + b"".join(n.encode() + b"\0" for n in names)
    name_off = {n: shstr.index(n.encode() + b"\0") for n in names}

    ehsize, phentsize, shentsize = 52, 32, 40
    phnum = len(progbits) + len(nobits)
    data_off = ehsize + phnum * phentsize
    body, phdrs, shdrs = b"", [], [b"\0" * shentsize]
    for name, flags, addr, data in progbits:
        off = data_off + len(body)
        pflags = 5 if flags & SHF_EXEC else 6
        phdrs.append(struct.pack("<8I", 1, off, addr, addr, len(data), len(data), pflags, 4))
        shdrs.append(struct.pack("<10I", name_off[name], SHT_PROGBITS, flags, addr, off, len(data), 0, 0, 4, 0))
        body += data + b"\0" * (-len(data) % 4)
    for name, flags, addr, size in nobits:
        pflags = 5 if flags & SHF_EXEC else 6
        phdrs.append(struct.pack("<8I", 1, 0, addr, addr, 0, size, pflags, 4))
        shdrs.append(struct.pack("<10I", name_off[name], SHT_NOBITS, flags, addr, 0, size, 0, 0, 4, 0))
    shstr_off = data_off + len(body)
    body += shstr + b"\0" * (-len(shstr) % 4)
    shdrs.append(struct.pack("<10I", name_off[".shstrtab"], SHT_STRTAB, 0, 0, shstr_off, len(shstr), 0, 0, 1, 0))
    shoff = data_off + len(body)
    ident = b"\x7fELF" + bytes([1, 1, 1, 0]) + b"\0" * 8
    ehdr = ident + struct.pack("<HHIIIIIHHHHHH", 2, EM_XTENSA, 1, entry, ehsize, shoff, 0x300,
                               ehsize, phentsize, phnum, shentsize, len(shdrs), len(shdrs) - 1)
    return ehdr + b"".join(phdrs) + body + b"".join(shdrs), progbits, nobits


if __name__ == "__main__":
    elf, progbits, nobits = build(open(sys.argv[1], "rb").read())
    open(sys.argv[2], "wb").write(elf)
    for name, _, addr, data in progbits:
        print(f"{name:12} {addr:#010x} {len(data):#x}")
    for name, _, addr, size in nobits:
        print(f"{name:12} {addr:#010x} {size:#x} (nobits)")
