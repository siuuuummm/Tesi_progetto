#!/usr/bin/env python3
"""Confronta il comportamento dell'originale compilato a O1-O3 con quello a O0."""
import json, subprocess, sys, tempfile, pathlib

def run(binp, t):
    try:
        r = subprocess.run([str(binp)] + [str(a) for a in t.get("args", [])],
                           input=t.get("stdin", ""), capture_output=True,
                           text=True, errors="replace", timeout=5)
        return r.stdout, r.returncode
    except subprocess.TimeoutExpired:
        return "TIMEOUT", -1

for name in sys.argv[1:]:
    src = pathlib.Path("originals") / f"{name}.c"
    tf = pathlib.Path("originals") / f"{name}.tests.json"
    tests = json.loads(tf.read_text()) if tf.exists() else [{"args": [], "stdin": ""}]
    tmp = pathlib.Path(tempfile.mkdtemp())
    bins = {}
    for lv in ["O0", "O1", "O2", "O3"]:
        b = tmp / f"{name}_{lv}"
        subprocess.run(["gcc", f"-{lv}", "-w", str(src), "-o", str(b), "-lm"], check=True)
        bins[lv] = b
    ref = [run(bins["O0"], t) for t in tests]
    print(f"\n=== {name} ===")
    for lv, b in bins.items():
        res = [run(b, t) for t in tests]
        ok = sum(r == e for r, e in zip(res, ref))
        print(f"{lv}: {ok}/{len(tests)} test uguali a O0")
        for i, (r, e) in enumerate(zip(res, ref)):
            if r != e:
                print(f"   test {i} args={tests[i].get('args')}  exit O0={e[1]} {lv}={r[1]}")
                print(f"      O0 : {e[0][-200:]!r}")
                print(f"      {lv} : {r[0][-200:]!r}")
