"""Rende l'output di Ghidra compilabile solo in modo additivo: tipi di Ghidra,
header standard, prototipi delle funzioni e main rinominato. I corpi restano identici."""
import re, sys
from pathlib import Path
HEADER = """#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
typedef unsigned char undefined; typedef unsigned char undefined1; typedef unsigned short undefined2;
typedef unsigned int undefined3; typedef unsigned int undefined4; typedef unsigned long undefined5;
typedef unsigned long undefined6; typedef unsigned long undefined7; typedef unsigned long undefined8;
typedef unsigned char byte; typedef unsigned char uchar; typedef unsigned short ushort;
typedef unsigned int uint; typedef unsigned long ulong; typedef long long longlong;
typedef unsigned long long ulonglong; typedef void code;
"""
raw, dst = Path(sys.argv[1]), Path(sys.argv[2])
for f in sorted(raw.glob("cwe*.c")):
    testo = f.read_text()
    main = re.search(r"// main: (\w+)", testo).group(1)
    firme = re.findall(r"^(\w[^\n;{}]*\))\s*\n\s*\{", testo, re.M)
    corpo = re.sub(rf"\b{main}\b", "main", testo)
    proto = "".join(re.sub(rf"\b{main}\b", "main", s) + ";\n" for s in firme if not re.search(rf"\b{main}\b", s))
    nome = f.stem.replace("_", "_", 1)  # cwe119_O0
    (dst / f"{nome}_llm.c").write_text(HEADER + proto + corpo)
    print(nome, len(firme), "funzioni")
