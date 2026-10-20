#!/bin/sh
# Baseline con il solo Ghidra: compila e priva dei simboli i cinque programmi da
# O0 a O3, esporta il decompilato del main e delle funzioni raggiungibili, lo rende
# compilabile con sole dichiarazioni (assembla.py) e lo valuta con la stessa
# pipeline delle ricostruzioni dei modelli. Scrive risultati.csv e decompilato/.
set -e
QUI="$(cd "$(dirname "$0")" && pwd)"
TESI_ROOT="${TESI_ROOT:-$(cd "$QUI/../../.." && pwd)}"
AST="$TESI_ROOT/Programs/Experiments/Python AST controller"
GHIDRA="$TESI_ROOT/ghidra_11.3.2_PUBLIC/support/analyzeHeadless"
LAVORO="$(mktemp -d)"
mkdir -p "$LAVORO/bin" "$LAVORO/raw" "$LAVORO/proj" "$LAVORO/root/originals" "$LAVORO/root/ghidra"

for c in cwe119 cwe134 cwe190 cwe193 cwe416; do
  cp "$AST/originals/$c.c" "$AST/originals/$c.tests.json" "$LAVORO/root/originals/"
  for l in O0 O1 O2 O3; do
    gcc -$l "$AST/originals/$c.c" -o "$LAVORO/bin/${c}_$l" -lm 2>/dev/null
    strip --strip-all "$LAVORO/bin/${c}_$l"
    "$GHIDRA" "$LAVORO/proj" "P_${c}_$l" -import "$LAVORO/bin/${c}_$l" \
      -scriptPath "$QUI" -postScript ExportBaseline.py "$LAVORO/raw/${c}_$l.c" \
      -deleteProject > "$LAVORO/raw/${c}_$l.log" 2>&1
    echo "$c $l esportato"
  done
done

python3 "$QUI/assembla.py" "$LAVORO/raw" "$LAVORO/root/ghidra"
(cd "$LAVORO/root" && python3 "$AST/run_benchmark.py" --root . --out baseline.csv --no-ted)
mkdir -p "$QUI/decompilato"
cp "$LAVORO/root/baseline.csv" "$QUI/risultati.csv"
cp "$LAVORO/root/ghidra/"*.c "$QUI/decompilato/"
echo "Fatto: $QUI/risultati.csv (cartella di lavoro: $LAVORO)"
