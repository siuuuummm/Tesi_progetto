"""
run_benchmark.py — Esecuzione batch di ast_analyzer e raccolta in CSV wide

Struttura attesa:
    benchmark/
    ├── originals/        ← un file .c per funzione  (es. koch.c)
    ├── llm4decompile/    ← file decompilati         (es. koch_O0.c)
    ├── ghidra/           ← altra cartella/modello   (es. koch_O0.c)
    └── ...               ← quante cartelle/modelli vuoi

Output CSV wide (una riga per funzione × modello × livello):
    funzione, modello, livello, re_executability, edit_similarity,
    ast_node_similarity, tree_edit_distance, fanout_similarity,
    ast_depth_orig, ast_depth_dec, ast_depth_delta,
    cf_delta, decl_delta, expr_delta, lit_delta, stmt_delta

Uso:
    python run_benchmark.py                         # cerca ./benchmark
    python run_benchmark.py --root /path/to/bench   # cartella custom
    python run_benchmark.py --no-ted                # salta TED (più veloce)
    python run_benchmark.py --out risultati.csv     # nome output custom
"""

import os
import sys
import json
import csv
import argparse
import subprocess
from pathlib import Path

# ---------------------------------------------------------------------------
# Costanti
# ---------------------------------------------------------------------------
ORIGINALS_DIR = "originals"
LEVELS = {"O0", "O1", "O2", "O3"}

CSV_COLUMNS = [
    "funzione",
    "modello",
    "livello",
    "variante",          # nome file senza estensione, es. koch_O0_llm_2
    "re_executability",
    "functional_match",      # 1 se stdout+exit code coincidono su tutti i casi di test
    "functional_pass_rate",  # % di casi di test superati
    "compile_error_type",    # categoria più frequente tra gli errori gcc/ld
    "compile_error_count",   # numero di errori gcc/ld
    "asan_orig",             # errori ASan dell'originale (es. stack-buffer-overflow, none)
    "asan_dec",              # errori ASan del decompilato
    "asan_match",            # 1 se stessi errori ASan caso per caso (vuoto = N/A)
    "loc_orig",              # righe di codice (senza commenti/righe vuote)
    "loc_dec",
    "funcs_orig",            # numero di funzioni definite
    "funcs_dec",
    "edit_similarity",
    "ast_node_similarity",
    "tree_edit_distance",
    "fanout_similarity",
    "ast_depth_orig",
    "ast_depth_dec",
    "ast_depth_delta",
    "cf_delta",           # control_flow delta
    "decl_delta",         # declarations delta
    "expr_delta",         # expressions delta
    "lit_delta",          # literals delta
    "stmt_delta",         # statements delta
    "parse_error",        # 1 se il parsing AST è fallito, 0 altrimenti
    "sandbox_violations", # accessi fuori sandbox nel log di Goose (vuoto = dato assente)
]

# ---------------------------------------------------------------------------
# Percorso di ast_analyzer.py: cerca nella stessa cartella di questo script
# ---------------------------------------------------------------------------
ANALYZER = Path(__file__).parent / "ast_analyzer.py"


# ---------------------------------------------------------------------------
# Utilità
# ---------------------------------------------------------------------------
def discover_models(root: Path) -> list[str]:
    """Restituisce le cartelle modello (tutto tranne 'originals' e gli Archivio*)."""
    return sorted(
        d.name
        for d in root.iterdir()
        if d.is_dir() and d.name != ORIGINALS_DIR
        and not d.name.startswith((".", "Archivio"))
    )


def discover_functions(root: Path) -> list[tuple[str, Path]]:
    """Restituisce [(nome_funzione, path_originale), …]."""
    orig_dir = root / ORIGINALS_DIR
    if not orig_dir.is_dir():
        print(f"[ERRORE] Cartella '{ORIGINALS_DIR}' non trovata in {root}", file=sys.stderr)
        sys.exit(1)
    return sorted(
        (p.stem, p)
        for p in orig_dir.glob("*.c")
    )


def find_decompiled(root: Path, model: str, func: str) -> list[tuple[str, str, Path]]:
    """
    Cerca TUTTI i file decompilati per un dato modello e funzione.
    Ritorna [(livello, variante, path), ...] dove variante e il nome
    del file senza estensione, es. "koch_O0_llm_2".

    Gestisce qualsiasi naming convention purche il file inizi con
    {funzione}_{livello}, es.:
        koch_O0.c        -> livello=O0, variante=koch_O0
        koch_O0_llm.c    -> livello=O0, variante=koch_O0_llm
        koch_O1_llm_2.c  -> livello=O1, variante=koch_O1_llm_2
    """
    model_dir = root / model
    results = []
    for level in sorted(LEVELS):
        matches = sorted(model_dir.glob(f"{func}_{level}*.c"))
        for path in matches:
            variante = path.stem   # nome file senza .c
            results.append((level, variante, path))
    return results


def run_analyzer(original: Path, decompiled: Path, no_ted: bool,
                 no_functional: bool, no_asan: bool) -> dict:
    """
    Chiama ast_analyzer.py --json e ritorna il dizionario JSON risultante.
    In caso di errore ritorna un dict con solo l'indicatore di errore.
    """
    cmd = [sys.executable, str(ANALYZER), str(original), str(decompiled), "--json"]
    if no_ted:
        cmd.append("--no-ted")
    if no_functional:
        cmd.append("--no-functional")
    if no_asan:
        cmd.append("--no-asan")

    try:
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            timeout=120,
        )
        # stdout = JSON, stderr = report testuale (lo ignoriamo)
        if not result.stdout.strip():
            return {"_error": f"Nessun output JSON. stderr: {result.stderr[:200]}"}
        return json.loads(result.stdout)
    except subprocess.TimeoutExpired:
        return {"_error": "Timeout (>120s)"}
    except json.JSONDecodeError as e:
        return {"_error": f"JSON non valido: {e}"}
    except Exception as e:
        return {"_error": str(e)}


def extract_row(func: str, model: str, level: str, variante: str, data: dict) -> dict:
    """
    Trasforma il JSON di ast_analyzer in una riga CSV wide.
    """
    row: dict = {
        "funzione": func,
        "modello":  model,
        "livello":  level,
        "variante": variante,
    }

    if "_error" in data:
        # Errore di esecuzione dello script stesso
        row.update({c: "" for c in CSV_COLUMNS if c not in row})
        row["parse_error"] = data["_error"]
        return row

    # Re-executability
    rex = data.get("re_executability", {})
    row["re_executability"] = 1 if rex.get("success") else 0

    # Functional match (vuoto se disabilitato o se l'originale non compila)
    fun = data.get("functional") or {}
    match = fun.get("match")
    row["functional_match"] = "" if match is None else int(match)
    row["functional_pass_rate"] = _fmt(fun.get("pass_rate"))

    # Errori di build per categoria
    cats = rex.get("error_categories") or {}
    row["compile_error_type"]  = max(cats, key=cats.get) if cats else ""
    row["compile_error_count"] = sum(cats.values()) if cats else 0

    # AddressSanitizer (vuoto se libasan non disponibile o build fallita)
    asan = data.get("asan") or {}
    if asan and not asan.get("error"):
        row["asan_orig"]  = _asan_types(asan["orig"])
        row["asan_dec"]   = _asan_types(asan["dec"])
        row["asan_match"] = int(asan["match"])

    # Dimensione
    size = data.get("size", {})
    for key in ("loc_orig", "loc_dec", "funcs_orig", "funcs_dec"):
        row[key] = "" if size.get(key) is None else size[key]

    # Metriche continue
    row["edit_similarity"]    = _fmt(data.get("edit_similarity_pct"))
    row["ast_node_similarity"] = _fmt(data.get("ast_node_histogram_similarity_pct"))
    ted = data.get("tree_edit_distance", {})
    row["tree_edit_distance"] = _fmt(ted.get("similarity_pct"))
    row["fanout_similarity"]  = _fmt(data.get("fanout_similarity_pct"))

    # Profondità AST
    depth = data.get("ast_depth", {})
    row["ast_depth_orig"]  = depth.get("original", "")
    row["ast_depth_dec"]   = depth.get("decompiled", "")
    row["ast_depth_delta"] = depth.get("delta", "")

    # Profilo strutturale — solo i delta
    profile = data.get("structural_profile", {})
    row["cf_delta"]   = profile.get("control_flow",  {}).get("delta", "")
    row["decl_delta"] = profile.get("declarations",  {}).get("delta", "")
    row["expr_delta"] = profile.get("expressions",   {}).get("delta", "")
    row["lit_delta"]  = profile.get("literals",      {}).get("delta", "")
    row["stmt_delta"] = profile.get("statements",    {}).get("delta", "")

    row["parse_error"] = 1 if data.get("ast_error") else 0

    return row


def read_sandbox_violations(decompiled: Path) -> int | str:
    """Numero di violazioni registrate da auto_pipeline nel .meta.json del run."""
    meta = decompiled.with_suffix(".meta.json")
    if not meta.is_file():
        return ""
    try:
        return len(json.loads(meta.read_text(encoding="utf-8")).get("sandbox_violations", []))
    except (json.JSONDecodeError, OSError):
        return ""


def _asan_types(per_case: list) -> str:
    """Tipi di errore ASan distinti sui casi di test, es. 'stack-buffer-overflow'."""
    return ";".join(sorted({t or "none" for t in per_case}))


def _fmt(val) -> str:
    """Formatta float con 2 decimali, lascia vuoto se None/NaN."""
    if val is None:
        return ""
    try:
        f = float(val)
        import math
        return "" if math.isnan(f) else f"{f:.2f}"
    except (TypeError, ValueError):
        return ""


# ---------------------------------------------------------------------------
# Progress bar minimale (nessuna dipendenza esterna)
# ---------------------------------------------------------------------------
def _progress(current: int, total: int, label: str = ""):
    bar_w = 30
    filled = round(current / total * bar_w) if total else 0
    bar = "█" * filled + "░" * (bar_w - filled)
    pct = current / total * 100 if total else 0
    print(f"\r  [{bar}] {pct:5.1f}%  {label:<40}", end="", flush=True)


# ---------------------------------------------------------------------------
# main
# ---------------------------------------------------------------------------
def main():
    parser = argparse.ArgumentParser(
        description="Batch benchmark decompilazione → CSV wide",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__,
    )
    parser.add_argument(
        "--root", default="benchmark",
        help="Cartella radice del benchmark (default: ./benchmark)",
    )
    parser.add_argument(
        "--out", default="results.csv",
        help="File CSV di output (default: results.csv)",
    )
    parser.add_argument(
        "--no-ted", action="store_true",
        help="Salta il Tree Edit Distance (molto più veloce su file grandi)",
    )
    parser.add_argument(
        "--no-functional", action="store_true",
        help="Salta il test funzionale (nessuna esecuzione dei programmi)",
    )
    parser.add_argument(
        "--no-asan", action="store_true",
        help="Salta il controllo con AddressSanitizer",
    )
    parser.add_argument(
        "--force", action="store_true",
        help="Riesegui anche le righe già presenti nel CSV (default: skip)",
    )
    args = parser.parse_args()

    root = Path(args.root).resolve()
    if not root.is_dir():
        print(f"[ERRORE] Cartella benchmark non trovata: {root}", file=sys.stderr)
        print("  Crea la struttura con: mkdir -p benchmark/originals benchmark/llm4decompile benchmark/ghidra")
        sys.exit(1)

    if not ANALYZER.is_file():
        print(f"[ERRORE] ast_analyzer.py non trovato in {ANALYZER.parent}", file=sys.stderr)
        sys.exit(1)

    models    = discover_models(root)
    functions = discover_functions(root)

    if not models:
        print("[ERRORE] Nessuna cartella modello trovata (solo 'originals' presente).", file=sys.stderr)
        sys.exit(1)

    if not functions:
        print(f"[ERRORE] Nessun file .c trovato in {root / ORIGINALS_DIR}", file=sys.stderr)
        sys.exit(1)

    print(f"\n  Benchmark root : {root}")
    print(f"  Modelli trovati: {', '.join(models)}")
    print(f"  Funzioni trovate: {len(functions)}  ({', '.join(f for f, _ in functions[:5])}" +
          (" …" if len(functions) > 5 else "") + ")")
    print(f"  Output CSV     : {args.out}")
    print(f"  Tree Edit Dist : {'disabilitato (--no-ted)' if args.no_ted else 'abilitato'}")
    print()

    # Carica righe già esistenti (per lo skip intelligente)
    out_path = Path(args.out)
    existing_keys: set[tuple] = set()
    existing_rows: list[dict] = []

    if out_path.is_file() and not args.force:
        with open(out_path, newline="", encoding="utf-8") as f:
            reader = csv.DictReader(f)
            raw_rows = list(reader)

        # Deduplica: se esiste una riga con variante e una senza per la stessa
        # (funzione, modello, livello), teniamo solo quella con variante.
        seen: dict[tuple, dict] = {}
        for row in raw_rows:
            key = (row["funzione"], row["modello"], row["livello"])
            variante = row.get("variante", "").strip()
            prev = seen.get(key)
            if prev is None:
                seen[key] = row
            else:
                prev_var = prev.get("variante", "").strip()
                # Preferisce la riga con variante non vuota
                if variante and not prev_var:
                    seen[key] = row
                # Se entrambe hanno variante, le teniamo entrambe con chiave estesa
                elif variante and prev_var and variante != prev_var:
                    seen[(row["funzione"], row["modello"], row["livello"], variante)] = row
                    # mantieni anche la precedente con chiave estesa
                    seen[(prev["funzione"], prev["modello"], prev["livello"], prev_var)] = prev
                    del seen[key]

        existing_rows = list(seen.values())
        for row in existing_rows:
            existing_keys.add((row["funzione"], row["modello"], row["livello"], row.get("variante", "").strip()))
        print(f"  Righe esistenti: {len(existing_rows)} (usa --force per ricalcolare)")
        print()

    # Conta totale job
    jobs = [
        (func, orig, model, level, variante, dec_path)
        for func, orig in functions
        for model in models
        for level, variante, dec_path in find_decompiled(root, model, func)
        if (func, model, level, variante) not in existing_keys
    ]

    if not jobs:
        print("  Nessun nuovo job da eseguire. CSV già aggiornato.")
        return

    print(f"  Job da eseguire: {len(jobs)}")
    print()

    new_rows: list[dict] = []
    errors = 0

    for i, (func, orig, model, level, variante, dec_path) in enumerate(jobs):
        label = f"{func} / {model} / {variante}"
        _progress(i, len(jobs), label)

        data = run_analyzer(orig, dec_path, args.no_ted, args.no_functional, args.no_asan)
        row  = extract_row(func, model, level, variante, data)
        row["sandbox_violations"] = read_sandbox_violations(dec_path)
        new_rows.append(row)

        if "_error" in data or row.get("parse_error") not in (0, "0", ""):
            errors += 1

    _progress(len(jobs), len(jobs), "completato")
    print()

    # Scrivi CSV (righe esistenti + nuove, ordinate)
    all_rows = existing_rows + new_rows
    all_rows.sort(key=lambda r: (r["funzione"], r["modello"], r["livello"]))

    with open(out_path, "w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=CSV_COLUMNS, extrasaction="ignore")
        writer.writeheader()
        writer.writerows(all_rows)

    print(f"\n  ✔ CSV scritto: {out_path}  ({len(all_rows)} righe totali)")
    if errors:
        print(f"  ⚠ {errors} righe con errori di parsing (campo parse_error=1)")
    print()


if __name__ == "__main__":
    main()
