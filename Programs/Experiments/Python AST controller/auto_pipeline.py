"""
auto_pipeline.py — Pipeline completa di decompilazione e benchmark
====================================================================
Flusso automatizzato:
  Per ogni file .c in EXPERIMENTS_DIR, per ogni livello O0..O3:
    1. Compila con gcc -O{livello}
    2. Strip del binario
    3. Avvia Ghidra Headless + MCP server in background
    4. Lancia Goose con il prompt di reverse engineering, dentro una sandbox
       (cartella temporanea in /tmp con solo il binario: niente sorgenti,
       log o run precedenti, nessun nome di funzione nei percorsi)
    5. Sposta il file _llm.c prodotto nella cartella del modello corrente,
       con accanto un .meta.json (incluse le eventuali violazioni della sandbox)
    6. Aggiorna il CSV di benchmark con ast_analyzer

Uso:
    python auto_pipeline.py --source koch.c
    python auto_pipeline.py --source koch.c --levels O0 O1
    python auto_pipeline.py --source koch.c --levels O0 --run 2
    python auto_pipeline.py --source koch.c --dry-run

Configurazione: modifica la sezione CONFIG qui sotto, oppure usa
un file config.toml nella stessa cartella (vedi fondo file).
"""

import os
import sys
import time
import shutil
import subprocess
import argparse
import json
import csv
import math
import re
import hashlib
import tempfile
from datetime import datetime
from pathlib import Path

# ===========================================================================
# CONFIG — modifica questi percorsi per il tuo sistema
# ===========================================================================
# Radice della tesi: si imposta con la variabile d'ambiente TESI_ROOT.
# Se non è impostata, vale il percorso del portatile.
TESI_ROOT = Path(os.environ.get("TESI_ROOT", "/var/home/pippo/Desktop/Universita/Tesi"))
_AST = TESI_ROOT / "Programs" / "Experiments" / "Python AST controller"

CONFIG = {
    # Percorsi strumenti
    "ghidra_path":         str(TESI_ROOT / "ghidra_11.3.2_PUBLIC"),
    "ghidra_mcp_script":   str(TESI_ROOT / "GhidraMCP-release-1-4" / "ghidra_mcp_server.py"),
    "goose_bin":           shutil.which("goose") or str(Path.home() / ".local" / "bin" / "goose"),

    # Cartelle di lavoro
    "experiments_dir":     str(TESI_ROOT / "Programs" / "Experiments" / "Secfocus"),
    "benchmark_root":      str(_AST),
    "originals_dir":       str(_AST / "originals"),  # dentro benchmark_root

    # Modello corrente (nome della sottocartella nel benchmark_root)
    # Cambia questo quando cambi modello in Goose
    "current_model":       "gpt4_1",

    # Attesa avvio Ghidra (secondi) — aumenta se il server non è pronto in tempo
    "ghidra_startup_wait": 8,

    # Timeout Goose per singola sessione (secondi)
    "goose_timeout":       1300,

    # Quanti "nudge" (solleciti a scrivere il file) inviare se Goose si ferma
    # a chiedere conferma invece di scrivere. 2 = robusto senza sprecare token.
    "max_nudges":          2,

    # Porta MCP server Ghidra
    "mcp_port":            8080,
}

# Prompt base e nudge — {llm_output} viene sostituito a runtime
GOOSE_PROMPT = """\
Sei un esperto di Reverse Engineering. La tua missione è ricostruire \
l'intero codice sorgente C originale partendo dal binario fornito (stripped) \
usando l'estensione ghidra-mcp.

Il codice che produci deve essere una TRADUZIONE FEDELE del binario, non una \
tua reimplementazione di ciò che il programma sembra fare. Ogni riga che scrivi \
deve derivare da output che hai effettivamente letto dai tool.

STRATEGIA (segui questo ordine esatto, senza mai fermarti a chiedere conferma):

FASE 1 — ORIENTAMENTO
- Chiama list_functions per ottenere tutte le funzioni disponibili.
- Chiama list_strings per individuare costanti e messaggi utili.
- Annota mentalmente l'elenco completo delle FUN_...: dovrai decompilarle TUTTE.

FASE 2 — TROVA IL MAIN
- Decompila "entry" per trovare l'indirizzo del main (primo argomento di __libc_start_main).
- Se decompile_function fallisce, usa decompile_function_by_address con l'indirizzo \
numerico (es. 0x004003f0), poi prova disassemble_function con lo stesso indirizzo.
- Almeno uno dei tre metodi funziona: provali tutti prima di rinunciare.

FASE 3 — DECOMPILA LE FUNZIONI DEL PROGRAMMA
- Decompila il main. Poi segui le chiamate: decompila le FUN_... chiamate o \
referenziate dal main (anche tramite puntatori a funzione), e ricorsivamente \
quelle chiamate o referenziate da queste.
- NON decompilare le altre FUN_... dell'elenco: sono codice di avvio e chiusura \
inserito dal compilatore, non fanno parte del programma.
- Per ogni funzione usa decompile_function per nome. Solo se fallisce usa \
decompile_function_by_address; solo se fallisce anche questo usa \
disassemble_function. Non decompilare mai due volte la stessa funzione.
- Hai tempo e risorse illimitate: procedi con calma fino a esaurire le funzioni \
raggiungibili dal main.
- Prima di passare alla FASE 4, verifica di aver decompilato ogni funzione \
raggiungibile dal main.

FASE 4 — SCRIVI IL CODICE C
- Codice C completo, autonomo, compilabile con gcc senza errori.
- Riproduci ESATTAMENTE i valori numerici che leggi nel decompilato: costanti, \
delta, maschere, numero di round, dimensioni degli array, indici. Non arrotondare, \
non "correggere", non sostituire con valori tipici dell'algoritmo che credi di \
riconoscere. Se il decompilato mostra 0x1a2b3c4d, scrivi 0x1a2b3c4d.
- Riproduci la struttura di controllo osservata: stesso numero di iterazioni, \
stesse condizioni, stesso annidamento.
- Sostituisci i tipi Ghidra (undefined8, undefined4, byte, ulong) con i tipi C \
standard equivalenti per dimensione e segno (uint64_t, uint32_t, uint8_t, ...).
- Rinomina le FUN_... con nomi descrittivi basati su cosa fanno realmente.
- Includi tutti gli #include necessari (stdio.h, stdint.h, string.h, stdlib.h...).
- Mantieni la funzione main con la stessa logica di I/O e le stesse stringhe di \
formato osservate in list_strings.

FASE 5 — SALVA IL FILE (OBBLIGATORIO E FINALE)
- Usa il tool "write" dell'estensione developer (parametri: path, content) per \
salvare il codice nel file: {llm_output}
- Questo passo è NON NEGOZIABILE. Non terminare senza averlo completato.
- Dopo aver scritto il file scrivi esattamente la parola: DONE

DIVIETI ASSOLUTI (la violazione invalida l'intero lavoro):
- VIETATO scrivere codice segnaposto, scheletri, stub o funzioni vuote.
- VIETATO inserire commenti tipo "TODO", "implementare", "placeholder", \
"reconstructed from stripped binary", "logica omessa".
- VIETATO scrivere un main che si limita a una printf o a "return 0".
- VIETATO inventare l'implementazione di una funzione che non hai decompilato: \
se un tool non risponde, cambia metodo e riprova, non riempire il vuoto a memoria.
- VIETATO riscrivere l'algoritmo "da manuale" perché lo riconosci: devi trascrivere \
quello che c'è nel binario, anche se differisce dalla versione canonica.
- VIETATO correggere bug, overflow, chiamate insicure (strcpy, gets, sprintf, printf \
con formato non costante...) o controlli mancanti, anche se evidenti: il codice deve \
riprodurre anche gli errori del binario, perché servono per l'analisi delle vulnerabilità.

REGOLE OPERATIVE:
- Non fare MAI domande. Procedi sempre in autonomia.
- Un errore su un tool non è un motivo per fermarsi: cambia metodo e riprova.
- Non fermarti mai a metà sessione.
- VIETATO chiedere "Procedo?" o "Vuoi che scriva il file?": scrivi SEMPRE il file \
senza chiedere, ma solo dopo aver realmente decompilato tutte le funzioni.\
"""

# Secondo prompt inviato se Goose non ha scritto il file al primo tentativo
GOOSE_NUDGE = """\
Il file {llm_output} NON è stato ancora creato. \
Devi completare la FASE 5 adesso: usa il tool "write" dell'estensione developer \
(parametri: path, content) per salvare nel percorso esatto {llm_output} il codice C \
che hai già ricostruito dalle decompilazioni effettuate.

Scrivi il codice completo e reale ricavato dai tool: NON uno scheletro, NON un file \
con TODO o placeholder, NON un main vuoto. Se qualche funzione non è ancora stata \
decompilata, recuperala ora con decompile_function, decompile_function_by_address o \
disassemble_function, poi scrivi il file.

Non fare domande. Scrivi il file adesso e poi scrivi DONE.
"""

# ===========================================================================
# Utilità
# ===========================================================================

def log(msg: str, level: str = "INFO"):
    icons = {"INFO": "·", "OK": "✔", "WARN": "⚠", "ERR": "✘", "STEP": "▶"}
    icon = icons.get(level, "·")
    print(f"  [{icon}] {msg}", flush=True)


def separator(title: str = ""):
    w = 64
    if title:
        pad = w - len(title) - 4
        print(f"\n  ── {title} {'─' * max(0, pad)}")
    else:
        print(f"  {'─' * w}")


def kill_port(port: int):
    try:
        subprocess.run(["fuser", "-k", f"{port}/tcp"], capture_output=True)
    except Exception:
        pass


def run(cmd: list, check: bool = True, capture: bool = False,
        timeout: int = None, log_file: Path = None) -> subprocess.CompletedProcess:
    """Wrapper subprocess con gestione log opzionale."""
    if log_file:
        with open(log_file, "w") as lf:
            return subprocess.run(
                cmd, stdout=lf, stderr=subprocess.STDOUT,
                check=check, timeout=timeout,
            )
    return subprocess.run(
        cmd,
        capture_output=capture,
        check=check,
        timeout=timeout,
    )


# ===========================================================================
# Step 1 — Compilazione
# ===========================================================================

def compile_source(source: Path, level: str, out_dir: Path) -> Path:
    """Compila source.c con gcc -O{level}, restituisce il path del binario."""
    # Usa un nome generico "test" per non rivelare il nome al LLM
    binary = out_dir / f"test_{level}"
    log(f"gcc -{level}  →  {binary.name}")
    run(["gcc", f"-{level}", str(source), "-o", str(binary), "-lm"])
    return binary


# ===========================================================================
# Step 2 — Strip
# ===========================================================================

def strip_binary(binary: Path):
    log(f"strip --strip-all {binary.name}")
    run(["strip", "--strip-all", str(binary)])


# ===========================================================================
# Step 3 — Ghidra Headless
# ===========================================================================

def start_ghidra(binary: Path, cfg: dict, log_file: Path) -> subprocess.Popen:
    analyze_headless = Path(cfg["ghidra_path"]) / "support" / "analyzeHeadless"
    project_dir = Path("/tmp/ghidra_auto")
    project_dir.mkdir(exist_ok=True)
    project_name = f"Proj_{int(time.time())}"

    cmd = [
        str(analyze_headless),
        str(project_dir), project_name,
        "-import", str(binary),
        "-postScript", cfg["ghidra_mcp_script"],
        "-overwrite",
    ]
    log(f"Ghidra headless  →  log: {log_file.name}")
    with open(log_file, "w") as lf:
        proc = subprocess.Popen(cmd, stdout=lf, stderr=subprocess.STDOUT)

    wait = cfg["ghidra_startup_wait"]
    log(f"Attendo {wait}s avvio MCP server...")
    time.sleep(wait)
    return proc


# ===========================================================================
# Step 4 — Goose
# ===========================================================================

def _goose_run(prompt: str, cmd_base: list, log_file: Path,
               timeout: int, cwd: Path, append: bool = False) -> bool:
    """Esegue un singolo invocazione di Goose, loggando l'output."""
    cmd = cmd_base + ["--text", prompt]
    mode = "a" if append else "w"
    try:
        with open(log_file, mode) as lf:
            subprocess.run(
                cmd,
                stdout=lf, stderr=subprocess.STDOUT,
                check=True,
                timeout=timeout,
                cwd=cwd,
            )
        return True
    except subprocess.TimeoutExpired:
        return False
    except subprocess.CalledProcessError:
        return False


def _file_ok(path: Path) -> bool:
    """True se il file esiste ed ha contenuto significativo."""
    return path.exists() and path.stat().st_size > 20


def run_goose(llm_output: Path, cfg: dict, log_file: Path,
              sandbox: Path) -> tuple[bool, int]:
    """
    Lancia Goose con il prompt principale. Se il file non viene prodotto
    (es. Goose si ferma a chiedere conferma), invia automaticamente fino a
    `max_nudges` solleciti per forzare la scrittura. I solleciti riprendono
    la stessa sessione (--name + --resume), quindi il modello ha ancora in
    contesto le decompilazioni già fatte.
    Restituisce (file prodotto, numero di nudge usati).
    """
    # Nome sessione = nome casuale della sandbox: unico e senza info sul programma
    cmd_base   = [cfg["goose_bin"], "run", "--name", sandbox.name]
    timeout    = cfg["goose_timeout"]
    max_nudges = cfg.get("max_nudges", 2)

    total_attempts = 1 + max_nudges
    log(f"Goose tentativo 1/{total_attempts}  →  {llm_output.name}")
    log(f"  log: {log_file.name}")

    prompt1 = GOOSE_PROMPT.format(llm_output=str(llm_output))
    _goose_run(prompt1, cmd_base, log_file, timeout, sandbox, append=False)

    if _file_ok(llm_output):
        log(f"File prodotto al primo tentativo: {llm_output.stat().st_size} bytes", "OK")
        return True, 0

    # Loop di nudge
    nudge_prompt = GOOSE_NUDGE.format(llm_output=str(llm_output))
    for n in range(1, max_nudges + 1):
        log(f"File non ancora scritto — nudge {n}/{max_nudges}...", "WARN")
        with open(log_file, "a") as lf:
            lf.write(f"\n\n=== NUDGE {n}/{max_nudges} ===\n")

        _goose_run(nudge_prompt, cmd_base + ["--resume"], log_file, timeout,
                   sandbox, append=True)

        if _file_ok(llm_output):
            log(f"File prodotto dopo nudge {n}: {llm_output.stat().st_size} bytes", "OK")
            return True, n

    log(f"Goose non ha scritto il file dopo {max_nudges} nudge", "ERR")
    return False, max_nudges


# ===========================================================================
# Controllo sandbox — accessi fuori dalla cartella di lavoro
# ===========================================================================

# Righe dei tool call nel log di Goose, es. "    command: cat /path" o "    path: /path"
_TOOL_ARG_RE = re.compile(r"^\s*(command|path):\s*(.*)$")
_TOKEN_RE = re.compile(r"[^\s'\"=;|&<>()`]+")


def find_sandbox_violations(goose_log: Path, sandbox: Path, cfg: dict) -> list[str]:
    """
    Cerca nel log di Goose i tool call che toccano percorsi fuori dalla sandbox:
    cartelle del benchmark/esperimenti, la home dell'utente, risalite con '..',
    ricerche su '/'. È un controllo euristico: guarda solo la prima riga di
    ogni comando, quindi non sostituisce un vero isolamento (container/bwrap).
    """
    if not goose_log.exists():
        return []

    sandbox_str = str(sandbox.resolve())
    forbidden = [cfg["experiments_dir"], cfg["benchmark_root"], cfg["originals_dir"]]
    home = str(Path.home())
    if not sandbox_str.startswith(home):
        forbidden.append(home)

    violations = []
    for line in goose_log.read_text(errors="replace").splitlines():
        m = _TOOL_ARG_RE.match(line)
        if not m:
            continue
        arg = m.group(2).strip()
        for token in _TOKEN_RE.findall(arg):
            if token.startswith("~") or "$HOME" in token:
                token = os.path.expanduser(token.replace("$HOME", "~"))
            bad = (
                token == "/"
                or token.startswith("..")
                or (token.startswith("/")
                    and not os.path.normpath(token).startswith(sandbox_str)
                    and any(os.path.normpath(token).startswith(f) for f in forbidden))
            )
            if bad:
                violations.append(f"{m.group(1)}: {arg[:200]}")
                break

    return list(dict.fromkeys(violations))   # dedup mantenendo l'ordine


def write_run_metadata(dest: Path, meta: dict):
    """Salva {variante}.meta.json accanto al file decompilato."""
    meta_path = dest.with_suffix(".meta.json")
    meta_path.write_text(json.dumps(meta, indent=2, ensure_ascii=False), encoding="utf-8")
    log(f"Metadati  →  {meta_path.name}")


# ===========================================================================
# Step 5 — Sposta e rinomina il file prodotto
# ===========================================================================

def move_output(llm_output: Path, func_name: str, level: str,
                run_index: int, model: str, cfg: dict) -> Path:
    """
    Sposta llm_output nella cartella del modello corrente nel benchmark_root.
    Naming: {func}_{level}_llm.c  oppure  {func}_{level}_llm_{n}.c se run_index > 1
    """
    model_dir = Path(cfg["benchmark_root"]) / model
    model_dir.mkdir(exist_ok=True)

    suffix = "" if run_index == 1 else f"_{run_index}"
    dest_name = f"{func_name}_{level}_llm{suffix}.c"
    dest = model_dir / dest_name

    # Se esiste già, incrementa il suffisso automaticamente
    counter = run_index
    while dest.exists():
        counter += 1
        dest = model_dir / f"{func_name}_{level}_llm_{counter}.c"

    shutil.copy2(str(llm_output), str(dest))
    log(f"Spostato  →  {dest.relative_to(Path(cfg['benchmark_root']).parent)}", "OK")
    return dest


# ===========================================================================
# Step 6 — Benchmark
# ===========================================================================

def run_benchmark(cfg: dict, out_csv: str):
    """Lancia run_benchmark.py per aggiornare il CSV."""
    benchmark_script = Path(__file__).parent / "run_benchmark.py"
    ast_script = Path(__file__).parent / "ast_analyzer.py"

    if not benchmark_script.exists():
        log("run_benchmark.py non trovato — skip benchmark", "WARN")
        return
    if not ast_script.exists():
        log("ast_analyzer.py non trovato — skip benchmark", "WARN")
        return

    cmd = [
        sys.executable, str(benchmark_script),
        "--root", cfg["benchmark_root"],
        "--out", out_csv,
        # "--no-ted",  # decommentare per velocizzare (salta Tree Edit Distance)
    ]
    log("Aggiornamento CSV benchmark...")
    result = subprocess.run(cmd, capture_output=False)
    if result.returncode == 0:
        log(f"CSV aggiornato: {out_csv}", "OK")
    else:
        log("Benchmark completato con avvisi", "WARN")


# ===========================================================================
# Controlla se il file originale è già in originals/, se no lo copia
# ===========================================================================

def ensure_original(source: Path, cfg: dict):
    orig_dir = Path(cfg["originals_dir"])
    orig_dir.mkdir(parents=True, exist_ok=True)
    dest = orig_dir / source.name
    if not dest.exists():
        shutil.copy2(str(source), str(dest))
        log(f"Copiato in originals/: {source.name}", "OK")
    else:
        log(f"Già in originals/: {source.name}")


# ===========================================================================
# Pipeline per un singolo file × livello × run
# ===========================================================================

def process_one(source: Path, level: str, run_index: int, cfg: dict,
                out_csv: str, dry_run: bool):
    func_name = source.stem
    work_dir = Path(cfg["experiments_dir"]) / "Eseguibili" / func_name
    work_dir.mkdir(parents=True, exist_ok=True)

    separator(f"{func_name}  {level}  run#{run_index}")

    # I log restano in work_dir, fuori dalla sandbox in cui lavora Goose
    ghidra_log = work_dir / f"ghidra_{level}.log"
    goose_log  = work_dir / f"goose_{level}_run{run_index}.log"

    if dry_run:
        log(f"[DRY RUN] Compilerei: gcc -{level} {source.name} → <sandbox>/test_{level}")
        log(f"[DRY RUN] Goose lavorerebbe in /tmp/re_task_*/ e scriverebbe out.c")
        log(f"[DRY RUN] Destinazione: {cfg['benchmark_root']}/{cfg['current_model']}/")
        return True

    # Sandbox: cartella neutra con solo il binario; Goose vi gira come cwd e
    # il prompt contiene solo questo percorso (nessun nome di funzione)
    sandbox = Path(tempfile.mkdtemp(prefix="re_task_"))
    binary  = sandbox / f"test_{level}"
    llm_out = sandbox / "out.c"
    log(f"Sandbox  →  {sandbox}")

    try:
        # 1. Compila
        try:
            compile_source(source, level, sandbox)
        except subprocess.CalledProcessError:
            log(f"Compilazione fallita per {func_name} -{level}", "ERR")
            return False

        # 2. Strip (una copia resta in work_dir per riferimento)
        strip_binary(binary)
        shutil.copy2(binary, work_dir / binary.name)

        # 3. Ghidra
        kill_port(cfg["mcp_port"])
        ghidra_proc = start_ghidra(binary, cfg, ghidra_log)

        success, nudges = False, 0
        started = time.time()
        try:
            # 4. Goose
            success, nudges = run_goose(llm_out, cfg, goose_log, sandbox)
        finally:
            ghidra_proc.terminate()
            kill_port(cfg["mcp_port"])

        violations = find_sandbox_violations(goose_log, sandbox, cfg)
        if violations:
            log(f"{len(violations)} accessi fuori sandbox nel log di Goose:", "WARN")
            for v in violations[:5]:
                log(f"  {v[:120]}", "WARN")

        if success:
            # 5. Sposta
            dest = move_output(llm_out, func_name, level, run_index,
                               cfg["current_model"], cfg)
            prompt = GOOSE_PROMPT.format(llm_output=str(llm_out))
            write_run_metadata(dest, {
                "source": source.name,
                "model": cfg["current_model"],
                "level": level,
                "run": run_index,
                "timestamp": datetime.now().isoformat(timespec="seconds"),
                "duration_s": round(time.time() - started),
                "nudges": nudges,
                "goose_session": sandbox.name,
                # sandbox in /tmp ha nome casuale: lo normalizziamo per un hash stabile
                "prompt_sha256": hashlib.sha256(
                    prompt.replace(str(llm_out), "<OUT>").encode()).hexdigest()[:12],
                "goose_log": str(goose_log),
                "sandbox_violations": violations,
            })
        else:
            log(f"Controlla i log in: {work_dir}", "WARN")

        return success

    finally:
        shutil.rmtree(sandbox, ignore_errors=True)


# ===========================================================================
# main
# ===========================================================================

def main():
    parser = argparse.ArgumentParser(
        description="Pipeline completa: compile → strip → Ghidra+Goose → benchmark",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__,
    )
    parser.add_argument(
        "--source", required=True,
        help="File .c sorgente da processare (es. koch.c)",
    )
    parser.add_argument(
        "--levels", nargs="+", default=["O0", "O1", "O2", "O3"],
        choices=["O0", "O1", "O2", "O3"],
        help="Livelli di ottimizzazione (default: tutti e 4)",
    )
    parser.add_argument(
        "--run", type=int, default=1,
        help="Indice del run (default: 1). Usa 2 per un secondo test di conferma.",
    )
    parser.add_argument(
        "--model", default=None,
        help="Nome modello (sovrascrive current_model in CONFIG)",
    )
    parser.add_argument(
        "--out", default="results.csv",
        help="File CSV di output del benchmark (default: results.csv)",
    )
    parser.add_argument(
        "--no-benchmark", action="store_true",
        help="Salta il benchmark finale (solo genera i file)",
    )
    parser.add_argument(
        "--dry-run", action="store_true",
        help="Mostra cosa farebbe senza eseguire nulla",
    )
    args = parser.parse_args()

    cfg = CONFIG.copy()
    if args.model:
        cfg["current_model"] = args.model

    source = Path(args.source).resolve()
    if not source.exists():
        print(f"[ERRORE] File non trovato: {source}", file=sys.stderr)
        sys.exit(1)

    print(f"""
  ╔══════════════════════════════════════════════════════════════╗
  ║           AUTO PIPELINE — Decompilazione + Benchmark         ║
  ╠══════════════════════════════════════════════════════════════╣
  ║  Sorgente : {source.name:<50}║
  ║  Livelli  : {', '.join(args.levels):<50}║
  ║  Run #    : {args.run:<50}║
  ║  Modello  : {cfg['current_model']:<50}║
  ║  Output   : {args.out:<50}║
  ╚══════════════════════════════════════════════════════════════╝
""")

    # Copia l'originale in originals/ se non c'è già
    if not args.dry_run:
        ensure_original(source, cfg)

    results = {}
    for level in args.levels:
        ok = process_one(source, level, args.run, cfg, args.out, args.dry_run)
        results[level] = "✔ OK" if ok else "✘ FALLITO"

    # Riepilogo
    separator("Riepilogo")
    for level, status in results.items():
        print(f"    {level}  →  {status}")

    # Benchmark finale
    if not args.no_benchmark and not args.dry_run:
        separator("Benchmark")
        out_csv = str(Path(cfg["benchmark_root"]) / args.out)
        run_benchmark(cfg, out_csv)

    separator()
    print()


if __name__ == "__main__":
    main()
