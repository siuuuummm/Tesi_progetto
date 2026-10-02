"""
ast_analyzer.py — Benchmark per la qualità della decompilazione C
Metriche implementate (allineate al paper LLM4Decompile, EMNLP 2024):
  1. Re-executability   — compilazione GCC senza errori
 1b. Functional Match   — originale e decompilato vengono eseguiti sugli stessi
                          input e se ne confrontano stdout ed exit code
 1c. ASan               — tipo di errore di memoria (AddressSanitizer) per caso
                          di test, originale vs decompilato (come in DecLLM)
     Errori di build    — errori gcc/ld classificati per categoria
     Dimensione         — righe di codice e numero di funzioni
  2. Edit Similarity    — distanza di Levenshtein normalizzata sul testo sorgente
  3. AST Node Similarity— overlap normalizzato sull'istogramma dei nodi (metrica originale)
  4. Tree Edit Distance — Zhang-Shasha TED normalizzato (metrica strutturale vera)
  5. AST Depth Delta    — differenza di profondità massima degli alberi
  6. Fan-out Similarity — similarità nella distribuzione del numero di figli per nodo
  7. Structural Profile — breakdown per categoria di nodo (control flow, declarations, …)

Dipendenze: pycparser, zss
  pip install pycparser zss
"""

import os
import sys
import json
import shutil
import subprocess
import argparse
import tempfile
import math
import difflib
import re
from collections import defaultdict, Counter
from pycparser import c_ast, parse_file

try:
    import zss
    ZSS_AVAILABLE = True
except ImportError:
    ZSS_AVAILABLE = False

# ---------------------------------------------------------------------------
# Tipi Ghidra: gestiti tramite -D macro SOLO se non già typedef'd nel file.
# Bug noto: -Dundefined4=unsigned int trasforma
#   'typedef unsigned int undefined4;' → 'typedef unsigned int unsigned int;' → errore!
# Soluzione: rilevare i typedef presenti e non aggiungere la macro corrispondente.
# ---------------------------------------------------------------------------
GHIDRA_MACROS: dict[str, str] = {
    "undefined8":  "unsigned long long",
    "undefined4":  "unsigned int",
    "undefined2":  "unsigned short",
    "undefined1":  "unsigned char",
    "ulong":       "unsigned long",
    "ulonglong":   "unsigned long long",
    "_Bool":       "int",
}
STD_TYPE_MACROS: list[str] = [
    # Interi a larghezza fissa (<stdint.h>)
    "-Duint8_t=unsigned char",
    "-Duint16_t=unsigned short",
    "-Duint32_t=unsigned int",
    "-Duint64_t=unsigned long long",
    "-Dint8_t=signed char",
    "-Dint16_t=short",
    "-Dint32_t=int",
    "-Dint64_t=long long",
    "-Duintptr_t=unsigned long",
    "-Dintptr_t=long",
    # Tipi di dimensione/puntatore (<stddef.h>) — spesso usati dagli LLM
    "-Dsize_t=unsigned long",
    "-Dssize_t=long",
    "-Dptrdiff_t=long",
    "-Dwchar_t=int",
    "-Dchar16_t=unsigned short",
    "-Dchar32_t=unsigned int",
    # Tipi GCC a 128 bit che pycparser non conosce
    "-D__int128=long long",
    "-D__uint128_t=unsigned long long",
    "-D__int128_t=long long",
    # Macro interna di Ghidra
    "-DSUB168(a,b)=0",
]

# ---------------------------------------------------------------------------
# Costanti di categorizzazione nodi AST
# ---------------------------------------------------------------------------
NODE_CATEGORIES = {
    "control_flow": {
        "If", "For", "While", "DoWhile", "Switch", "Case", "Default",
        "Break", "Continue", "Goto", "Label",
    },
    "declarations": {
        "Decl", "FuncDecl", "ParamList", "Typename", "TypeDecl",
        "IdentifierType", "PtrDecl", "ArrayDecl", "Struct", "Union", "Enum",
        "Enumerator", "EnumeratorList", "StructOrUnion",
    },
    "expressions": {
        "Assignment", "BinaryOp", "UnaryOp", "TernaryOp", "Cast",
        "FuncCall", "ExprList", "NamedInitializer", "CompoundLiteral",
    },
    "literals": {
        "Constant", "ID", "ArrayRef", "StructRef",
    },
    "statements": {
        "Compound", "Return", "EmptyStatement", "FileAST", "DeclList",
    },
}

NODE_TO_CATEGORY = {}
for cat, nodes in NODE_CATEGORIES.items():
    for n in nodes:
        NODE_TO_CATEGORY[n] = cat


# ---------------------------------------------------------------------------
# Visitor: raccoglie conteggi, profondità, fan-out, struttura dell'albero
# ---------------------------------------------------------------------------
class ASTCollector(c_ast.NodeVisitor):
    def __init__(self):
        self.node_counts: Counter = Counter()
        self.total_nodes: int = 0
        self.max_depth: int = 0
        self.fanout_list: list[int] = []
        self._depth: int = 0

    def generic_visit(self, node):
        self._depth += 1
        self.max_depth = max(self.max_depth, self._depth)

        ntype = type(node).__name__
        self.node_counts[ntype] += 1
        self.total_nodes += 1

        children = list(node.children())
        self.fanout_list.append(len(children))

        super().generic_visit(node)
        self._depth -= 1

    def category_distribution(self) -> dict[str, int]:
        dist: dict[str, int] = defaultdict(int)
        for ntype, cnt in self.node_counts.items():
            cat = NODE_TO_CATEGORY.get(ntype, "other")
            dist[cat] += cnt
        return dict(dist)

    def avg_fanout(self) -> float:
        return sum(self.fanout_list) / len(self.fanout_list) if self.fanout_list else 0.0


# ---------------------------------------------------------------------------
# Conversione pycparser → zss.Node per il Tree Edit Distance
# ---------------------------------------------------------------------------
def _to_zss(node) -> "zss.Node":
    """Converte ricorsivamente un nodo pycparser in un albero zss."""
    label = type(node).__name__
    znode = zss.Node(label)
    for _, child in node.children():
        znode.addkid(_to_zss(child))
    return znode


def tree_edit_distance(ast1, ast2) -> tuple[float, float]:
    """
    Calcola lo Zhang-Shasha Tree Edit Distance tra due AST pycparser.
    Ritorna (ted_raw, ted_normalized).
    ted_normalized = 1 - ted / (size1 + size2)  (in [0,1], 1 = identici)
    """
    if not ZSS_AVAILABLE:
        return float("nan"), float("nan")

    z1 = _to_zss(ast1)
    z2 = _to_zss(ast2)

    ted = zss.simple_distance(z1, z2)

    # Dimensione albero = numero totale di nodi
    def tree_size(z: "zss.Node") -> int:
        return 1 + sum(tree_size(c) for c in z.children)

    s1 = tree_size(z1)
    s2 = tree_size(z2)
    denom = s1 + s2
    ted_norm = max(0.0, 1.0 - ted / denom) if denom > 0 else 1.0
    return float(ted), ted_norm


# ---------------------------------------------------------------------------
# Pulizia e parsing
# ---------------------------------------------------------------------------
def parse_c_file(filepath: str):
    """
    Rimuove le direttive #include, scrive un file temporaneo e lo parsa.

    I -D macro gestiscono i tipi custom di Ghidra, ma vengono aggiunti
    SOLO per i nomi che non sono già oggetto di 'typedef' nel file.
    Questo evita il conflitto critico:
        -Dundefined4=unsigned int  +  typedef unsigned int undefined4;
        → typedef unsigned int unsigned int;   ← ParseError!
    """
    with open(filepath, "r", encoding="utf-8", errors="replace") as f:
        content = f.read()

    # Rimuove #include
    clean_lines = [
        l for l in content.splitlines(keepends=True)
        if not l.strip().startswith("#include")
    ]

    # Individua i nomi già typedef'd nel sorgente
    already_typedefd: set[str] = set()
    for tname in GHIDRA_MACROS:
        if re.search(rf"typedef\b.*\b{re.escape(tname)}\s*;", content):
            already_typedefd.add(tname)

    # Costruisce la lista di -D evitando i conflitti
    cpp_args = STD_TYPE_MACROS[:]
    for tname, ttype in GHIDRA_MACROS.items():
        if tname not in already_typedefd:
            cpp_args.append(f"-D{tname}={ttype}")

    with tempfile.NamedTemporaryFile(suffix=".c", mode="w", delete=False) as tmp:
        tmp.writelines(clean_lines)
        tmp_path = tmp.name

    try:
        return parse_file(tmp_path, use_cpp=True, cpp_args=cpp_args)
    finally:
        os.unlink(tmp_path)


# ---------------------------------------------------------------------------
# Metrica 1 — Re-executability (compilazione)
# ---------------------------------------------------------------------------
def check_reexecutability(filepath: str) -> tuple[bool, str]:
    # Stessi flag di _build_executable (niente -std=c99): un file che compila qui
    # deve poter essere linkato ed eseguito dal test funzionale e viceversa.
    try:
        result = subprocess.run(
            ["gcc", "-c", "-x", "c", filepath, "-o", "/dev/null",
             "-w"],  # sopprimi warning, vogliamo solo errori fatali
            capture_output=True, text=True, timeout=15,
        )
        return result.returncode == 0, result.stderr.strip()
    except FileNotFoundError:
        return False, "gcc non trovato nel PATH"
    except subprocess.TimeoutExpired:
        return False, "Timeout durante la compilazione"
    except Exception as exc:
        return False, str(exc)


# Categorie ispirate a DecLLM §3 e LLM4Decompile Fig. 8; la prima che fa match vince
ERROR_CATEGORIES = [
    ("link",        r"undefined reference|multiple definition"),
    ("signature",   r"too (few|many) arguments"),   # "specification error" in DecLLM
    ("declaration", r"implicit declaration|undeclared|unknown type name|conflicting types"
                    r"|redefinition|redeclared|previous (declaration|definition)"),
    ("struct",      r"\bstruct\b|\bunion\b|has no member|incomplete type"),
    ("type",        r"incompatible type|invalid operands|invalid suffix|lvalue|cannot convert"
                    r"|subscripted value|invalid type argument|pointer|cast|initiali[sz]|read-only"),
    ("syntax",      r"expected|stray|missing terminating|unterminated|before"),
]


def classify_compiler_errors(stderr: str) -> dict[str, int]:
    """Conta gli errori di gcc/ld per categoria (declaration, type, struct, ...)."""
    counts: Counter = Counter()
    for line in stderr.splitlines():
        if "ld returned" in line:      # riga riassuntiva di collect2
            continue
        if "error:" not in line and "undefined reference" not in line \
                and "multiple definition" not in line:
            continue
        msg = line.split("error:", 1)[-1]
        for cat, rx in ERROR_CATEGORIES:
            if re.search(rx, msg):
                counts[cat] += 1
                break
        else:
            counts["other"] += 1
    return dict(counts)


# ---------------------------------------------------------------------------
# Metrica 1b — Functional Match (esecuzione e confronto dell'output)
# ---------------------------------------------------------------------------
# Il codice generato dall'LLM viene eseguito davvero: se bwrap è disponibile
# gira con filesystem in sola lettura, /tmp privato e senza rete; altrimenti
# solo con timeout dentro una cartella temporanea.
BWRAP = shutil.which("bwrap")
RUN_TIMEOUT = 5
DEFAULT_TEST_CASES = [{"args": [], "stdin": ""}]


def load_test_cases(original_path: str, tests_path: str | None = None) -> list[dict]:
    """
    Legge i casi di test da <originale>.tests.json (o dal path indicato).
    Formato: [{"args": ["foo"], "stdin": "..."}, ...]
    Senza file di test si usa un solo caso: nessun argomento, stdin vuoto.
    """
    path = tests_path or os.path.splitext(original_path)[0] + ".tests.json"
    if not os.path.isfile(path):
        return DEFAULT_TEST_CASES
    with open(path, encoding="utf-8") as f:
        cases = json.load(f)
    return [{"args": c.get("args", []), "stdin": c.get("stdin", "")} for c in cases]


def _build_executable(src: str, exe: str, extra_flags: tuple = ()) -> tuple[bool, str]:
    """Compila e linka src (stessi flag per originale e decompilato)."""
    try:
        result = subprocess.run(
            ["gcc", "-O0", "-w", *extra_flags, src, "-o", exe, "-lm"],
            capture_output=True, text=True, timeout=30,
        )
        return result.returncode == 0, result.stderr.strip()
    except FileNotFoundError:
        return False, "gcc non trovato nel PATH"
    except subprocess.TimeoutExpired:
        return False, "Timeout durante la compilazione"


def _run_case(exe_dir: str, case: dict,
              env: dict | None = None) -> tuple[int | str, bytes, bytes]:
    """
    Esegue <exe_dir>/prog sul caso di test. Ritorna (exit code, stdout, stderr);
    l'exit code è "timeout" se il programma non termina in RUN_TIMEOUT secondi.
    argv[0] è uguale per originale e decompilato, così l'output è confrontabile.
    """
    if BWRAP:
        cmd = [
            BWRAP, "--ro-bind", "/", "/", "--dev", "/dev", "--proc", "/proc",
            "--tmpfs", "/tmp", "--ro-bind", os.path.join(exe_dir, "prog"), "/tmp/prog",
            "--unshare-all", "--die-with-parent", "--chdir", "/tmp",
            "./prog", *case["args"],
        ]
    else:
        cmd = ["./prog", *case["args"]]
    try:
        result = subprocess.run(
            cmd, cwd=exe_dir, input=case["stdin"].encode(),
            stdout=subprocess.PIPE, stderr=subprocess.PIPE,
            timeout=RUN_TIMEOUT, env=env,
        )
        return result.returncode, result.stdout, result.stderr
    except subprocess.TimeoutExpired as exc:
        return "timeout", exc.stdout or b"", exc.stderr or b""


def _first_error(stderr: str) -> str:
    """Prima riga utile dell'output di gcc/ld (quella con 'error'), altrimenti la prima."""
    lines = stderr.splitlines()
    for line in lines:
        if "error" in line:
            return line.strip()
    return lines[0].strip() if lines else ""


def functional_test(original_path: str, decompiled_path: str, cases: list[dict]) -> dict:
    """
    Compila originale e decompilato, li esegue sugli stessi casi e confronta
    stdout ed exit code. pass_rate/match restano None se l'originale non compila
    (il test non è applicabile); se non compila il decompilato valgono 0/False.
    """
    result = {
        "original_built": False,
        "decompiled_built": False,
        "sandboxed": BWRAP is not None,
        "passed": 0,
        "total": len(cases),
        "pass_rate": None,
        "match": None,
        "error": None,
        "build_stderr": None,
        "failures": [],
    }

    with tempfile.TemporaryDirectory() as tmp:
        orig_dir = os.path.join(tmp, "orig")
        dec_dir = os.path.join(tmp, "dec")
        os.makedirs(orig_dir)
        os.makedirs(dec_dir)

        ok, err = _build_executable(original_path, os.path.join(orig_dir, "prog"))
        if not ok:
            result["error"] = f"l'originale non compila: {_first_error(err)}"
            return result
        result["original_built"] = True

        ok, err = _build_executable(decompiled_path, os.path.join(dec_dir, "prog"))
        if not ok:
            result["error"] = f"il decompilato non compila/linka: {_first_error(err)}"
            result["build_stderr"] = err[:4000]
            result["pass_rate"] = 0.0
            result["match"] = False
            return result
        result["decompiled_built"] = True

        for case in cases:
            exp_rc, exp_out, _ = _run_case(orig_dir, case)
            got_rc, got_out, _ = _run_case(dec_dir, case)
            reasons = []
            if exp_rc != got_rc:
                reasons.append(f"exit {exp_rc} vs {got_rc}")
            if exp_out != got_out:
                reasons.append("stdout diverso")
            if reasons:
                result["failures"].append({"args": case["args"], "reason": ", ".join(reasons)})
            else:
                result["passed"] += 1

    total = result["total"]
    result["pass_rate"] = result["passed"] / total * 100.0 if total else 0.0
    result["match"] = result["passed"] == total
    return result


# ---------------------------------------------------------------------------
# Metrica 1c — AddressSanitizer (errori di memoria, come in DecLLM §4.4)
# ---------------------------------------------------------------------------
ASAN_FLAGS = ("-g", "-fsanitize=address", "-fno-omit-frame-pointer")
# I leak non interessano: differenze nei free() non sono errori di decompilazione
ASAN_ENV = {"ASAN_OPTIONS": "detect_leaks=0"}
_ASAN_RE = re.compile(r"ERROR: AddressSanitizer: ([\w-]+)")
_asan_ok: bool | None = None


def asan_available() -> bool:
    """True se gcc riesce a linkare con -fsanitize=address (serve libasan)."""
    global _asan_ok
    if _asan_ok is None:
        with tempfile.TemporaryDirectory() as tmp:
            src = os.path.join(tmp, "probe.c")
            with open(src, "w") as f:
                f.write("int main(void) { return 0; }\n")
            _asan_ok, _ = _build_executable(src, os.path.join(tmp, "probe"), ASAN_FLAGS)
    return _asan_ok


def asan_test(original_path: str, decompiled_path: str, cases: list[dict]) -> dict | None:
    """
    Compila originale e decompilato con AddressSanitizer e registra, per ogni
    caso di test, il tipo di errore di memoria rilevato (None se nessuno).
    Per i programmi con comportamento indefinito (es. cwe119) confrontare il tipo
    di errore è più robusto che confrontare exit code e stdout.
    Ritorna None se libasan non è installata.
    """
    if not asan_available():
        return None

    result = {"orig": [], "dec": [], "match": None, "error": None}
    env = dict(os.environ, **ASAN_ENV)

    with tempfile.TemporaryDirectory() as tmp:
        dirs = {}
        for name, path in (("orig", original_path), ("dec", decompiled_path)):
            dirs[name] = os.path.join(tmp, name)
            os.makedirs(dirs[name])
            ok, err = _build_executable(path, os.path.join(dirs[name], "prog"), ASAN_FLAGS)
            if not ok:
                result["error"] = f"build ASan fallita ({name}): {_first_error(err)}"
                return result

        for case in cases:
            for name in ("orig", "dec"):
                _, _, stderr = _run_case(dirs[name], case, env)
                m = _ASAN_RE.search(stderr.decode(errors="replace"))
                result[name].append(m.group(1) if m else None)

    result["match"] = result["orig"] == result["dec"]
    return result


# ---------------------------------------------------------------------------
# Dimensione del codice (le prestazioni calano con la lunghezza, vedi i paper)
# ---------------------------------------------------------------------------
def count_loc(text: str) -> int:
    """Righe di codice non vuote, esclusi i commenti (approssimato)."""
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    text = re.sub(r"//[^\n]*", "", text)
    return sum(1 for line in text.splitlines() if line.strip())


# ---------------------------------------------------------------------------
# Metrica 2 — Edit Similarity (SequenceMatcher, come nel paper)
# ---------------------------------------------------------------------------
def edit_similarity(text1: str, text2: str) -> float:
    """
    Ratio di SequenceMatcher di Python ≈ 2*M / T
    dove M = numero di caratteri corrispondenti, T = totale caratteri.
    Restituisce un valore in [0, 100].
    """
    # Normalizziamo whitespace per un confronto più equo
    t1 = " ".join(text1.split())
    t2 = " ".join(text2.split())
    ratio = difflib.SequenceMatcher(None, t1, t2).ratio()
    return ratio * 100.0


# ---------------------------------------------------------------------------
# Metrica 3 — AST Node Histogram Similarity (dal paper originale)
# ---------------------------------------------------------------------------
def node_histogram_similarity(col1: ASTCollector, col2: ASTCollector) -> float:
    all_keys = set(col1.node_counts) | set(col2.node_counts)
    intersection = sum(min(col1.node_counts.get(k, 0), col2.node_counts.get(k, 0)) for k in all_keys)
    denom = max(col1.total_nodes, col2.total_nodes)
    return (intersection / denom * 100.0) if denom > 0 else 0.0


# ---------------------------------------------------------------------------
# Metrica 5 — Fan-out similarity (distribuzione del numero di figli)
# ---------------------------------------------------------------------------
def fanout_similarity(col1: ASTCollector, col2: ASTCollector) -> float:
    """
    Confronta le distribuzioni del fan-out usando la divergenza di Jensen-Shannon
    (più robusta della semplice differenza di medie).
    Restituisce un valore in [0, 100] (100 = distribuzioni identiche).
    """
    def dist(fanout_list: list[int]) -> dict[int, float]:
        c = Counter(fanout_list)
        total = sum(c.values())
        return {k: v / total for k, v in c.items()} if total else {}

    p = dist(col1.fanout_list)
    q = dist(col2.fanout_list)
    all_keys = set(p) | set(q)

    def js_divergence(p, q, keys) -> float:
        eps = 1e-12
        jsd = 0.0
        for k in keys:
            pk = p.get(k, 0.0) + eps
            qk = q.get(k, 0.0) + eps
            m = (pk + qk) / 2
            jsd += pk * math.log(pk / m) + qk * math.log(qk / m)
        return jsd / 2.0

    jsd = js_divergence(p, q, all_keys)
    # JSD ∈ [0, ln2]; normalizziamo a [0,1] e invertiamo per avere "similarità"
    similarity = max(0.0, 1.0 - jsd / math.log(2)) * 100.0
    return similarity


# ---------------------------------------------------------------------------
# Metrica 6 — Structural Profile (breakdown per categoria)
# ---------------------------------------------------------------------------
def structural_profile_diff(col1: ASTCollector, col2: ASTCollector) -> dict[str, dict]:
    cats = set(NODE_CATEGORIES.keys()) | {"other"}
    dist1 = col1.category_distribution()
    dist2 = col2.category_distribution()
    result = {}
    for cat in sorted(cats):
        n1 = dist1.get(cat, 0)
        n2 = dist2.get(cat, 0)
        result[cat] = {
            "original": n1,
            "decompiled": n2,
            "delta": n2 - n1,
            "delta_pct": ((n2 - n1) / n1 * 100.0) if n1 > 0 else float("inf") if n2 > 0 else 0.0,
        }
    return result


# ---------------------------------------------------------------------------
# Pretty printing
# ---------------------------------------------------------------------------
W = 64

def _sep(char="─"):
    return char * W

def _hdr(title: str):
    pad = W - len(title) - 2
    return f"┌{'─' * ((pad) // 2)} {title} {'─' * ((pad + 1) // 2)}┐"

def _bar(value: float, width: int = 30, char: str = "█") -> str:
    if math.isnan(value):
        return "░" * width
    filled = round(value / 100 * width)
    filled = max(0, min(width, filled))
    return char * filled + "░" * (width - filled)

def _color(value: float, low: float = 40.0, high: float = 70.0) -> str:
    """ANSI color: rosso < low, giallo < high, verde ≥ high."""
    if math.isnan(value):
        return "\033[90mN/A\033[0m"
    if value < low:
        return f"\033[91m{value:.1f}%\033[0m"
    elif value < high:
        return f"\033[93m{value:.1f}%\033[0m"
    else:
        return f"\033[92m{value:.1f}%\033[0m"


def print_report(
    orig_path: str,
    dec_path: str,
    can_compile: bool,
    compile_err: str,
    functional: dict | None,
    es: float,
    histo_sim: float,
    ted_raw: float,
    ted_norm: float,
    col_orig: ASTCollector,
    col_dec: ASTCollector,
    fanout_sim: float,
    profile_diff: dict,
    extra: dict,
):
    print()
    print(_hdr("LLM4Decompile — BENCHMARK REPORT"))
    print(f"  Originale  : {os.path.basename(orig_path)}")
    print(f"  Decompilato: {os.path.basename(dec_path)}")
    print(_sep())

    # 1. Re-executability
    status_str = "\033[92m✔ SUCCESS\033[0m" if can_compile else "\033[91m✘ FAILED\033[0m"
    print(f"\n  [1] RE-EXECUTABILITY (Compilazione GCC)")
    print(f"      Risultato : {status_str}")
    if not can_compile and compile_err:
        # mostra solo le prime 3 righe di errore per non sporcare l'output
        first_errors = "\n".join(compile_err.splitlines()[:3])
        print(f"      Errori    : {first_errors}")
    if extra["error_categories"]:
        cats = ", ".join(f"{k}={v}" for k, v in sorted(extra["error_categories"].items(),
                                                        key=lambda kv: -kv[1]))
        print(f"      Categorie : {cats}")

    # 1b. Functional Match
    print(f"\n  [1b] FUNCTIONAL MATCH (stdout + exit code vs originale)")
    if functional is None:
        print("      Disabilitato (--no-functional)")
    elif functional["pass_rate"] is None:
        print(f"      \033[90mN/A\033[0m — {functional['error']}")
    else:
        status = "\033[92m✔ MATCH\033[0m" if functional["match"] else "\033[91m✘ DIVERSO\033[0m"
        print(f"      Risultato : {status}  ({functional['passed']}/{functional['total']} casi)")
        if functional["error"]:
            print(f"      Errore    : {functional['error']}")
        for fail in functional["failures"][:3]:
            print(f"      Fallito   : args={fail['args']}  → {fail['reason']}")
        if not functional["sandboxed"]:
            print("      \033[93m⚠ bwrap non trovato: eseguito senza sandbox\033[0m")

    # 1c. ASan
    asan = extra["asan"]
    print(f"\n  [1c] ADDRESS SANITIZER (errori di memoria per caso di test)")
    if asan is None:
        print("      \033[90mN/A\033[0m — disabilitato o libasan non installata")
    elif asan["error"]:
        print(f"      \033[90mN/A\033[0m — {asan['error']}")
    else:
        status = "\033[92m✔ UGUALE\033[0m" if asan["match"] else "\033[91m✘ DIVERSO\033[0m"
        fmt = lambda xs: ", ".join(x or "nessuno" for x in xs)
        print(f"      Risultato   : {status}")
        print(f"      Originale   : {fmt(asan['orig'])}")
        print(f"      Decompilato : {fmt(asan['dec'])}")

    # Dimensione
    size = extra["size"]
    print(f"\n  [·] DIMENSIONE")
    print(f"      Righe di codice : {size['loc_orig']} → {size['loc_dec']}")
    if size["funcs_orig"] is not None:
        print(f"      Funzioni        : {size['funcs_orig']} → {size['funcs_dec']}")

    # 2. Edit Similarity
    print(f"\n  [2] EDIT SIMILARITY (testo sorgente)")
    print(f"      Score : {_color(es)}  {_bar(es)}")

    # 3. AST Histogram Similarity
    print(f"\n  [3] AST NODE SIMILARITY (istogramma, metrica paper)")
    print(f"      Score : {_color(histo_sim)}  {_bar(histo_sim)}")
    print(f"      Nodi originale   : {col_orig.total_nodes}")
    print(f"      Nodi decompilato : {col_dec.total_nodes}  (delta: {col_dec.total_nodes - col_orig.total_nodes:+d})")

    # 4. Tree Edit Distance
    print(f"\n  [4] TREE EDIT DISTANCE (Zhang-Shasha)")
    if math.isnan(ted_raw):
        print("      ⚠ zss non disponibile — installa con: pip install zss")
    else:
        ted_sim_pct = ted_norm * 100
        print(f"      TED raw        : {ted_raw:.0f} operazioni")
        print(f"      TED similarity : {_color(ted_sim_pct)}  {_bar(ted_sim_pct)}")
        note = "(strutturalmente vicini)" if ted_sim_pct >= 70 else \
               "(struttura parzialmente diversa)" if ted_sim_pct >= 40 else \
               "(struttura molto diversa)"
        print(f"      Nota           : {note}")

    # 5. Fan-out similarity
    print(f"\n  [5] FAN-OUT SIMILARITY (distribuzione figli per nodo)")
    print(f"      Avg fan-out orig : {col_orig.avg_fanout():.2f}")
    print(f"      Avg fan-out dec  : {col_dec.avg_fanout():.2f}")
    print(f"      JS similarity    : {_color(fanout_sim)}  {_bar(fanout_sim)}")

    # 6. Depth
    depth_delta = col_dec.max_depth - col_orig.max_depth
    depth_ok = abs(depth_delta) <= 3
    depth_icon = "\033[92m≈\033[0m" if depth_ok else "\033[91m≠\033[0m"
    print(f"\n  [6] PROFONDITÀ AST")
    print(f"      Profondità originale   : {col_orig.max_depth}")
    print(f"      Profondità decompilato : {col_dec.max_depth}  (delta: {depth_delta:+d}) {depth_icon}")

    # 7. Structural Profile
    print(f"\n  [7] PROFILO STRUTTURALE (nodi per categoria)")
    print(f"      {'Categoria':<16} {'Orig':>6} {'Dec':>6} {'Delta':>7}  {'Δ%':>8}")
    print(f"      {'─'*16} {'─'*6} {'─'*6} {'─'*7}  {'─'*8}")
    for cat, d in profile_diff.items():
        delta_pct_str = (
            f"{d['delta_pct']:>+7.1f}%"
            if math.isfinite(d["delta_pct"])
            else "    N/A"
        )
        print(f"      {cat:<16} {d['original']:>6} {d['decompiled']:>6} {d['delta']:>+7}  {delta_pct_str}")

    # Riepilogo
    print(f"\n  {_sep('═')}")
    scores = [es, histo_sim, fanout_sim]
    if not math.isnan(ted_norm):
        scores.append(ted_norm * 100)
    avg = sum(scores) / len(scores)
    verdict = (
        "\033[92mOTTIMO\033[0m"    if avg >= 70 else
        "\033[93mSUFFICIENTE\033[0m" if avg >= 45 else
        "\033[91mSCARSO\033[0m"
    )
    print(f"  Score medio (metriche continue): {avg:.1f}%  → {verdict}")
    print(f"  {'═' * W}")
    print()


# ---------------------------------------------------------------------------
# main
# ---------------------------------------------------------------------------
def main():
    parser = argparse.ArgumentParser(
        description="Benchmark AST per la qualità della decompilazione C (LLM4Decompile style)",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Esempio:
  python ast_analyzer.py original.c decompiled.c
  python ast_analyzer.py original.c decompiled.c --no-ted
        """,
    )
    parser.add_argument("original",   help="File C originale (ground truth)")
    parser.add_argument("decompiled", help="File C generato dall'LLM / Ghidra")
    parser.add_argument(
        "--no-ted", action="store_true",
        help="Salta il calcolo del Tree Edit Distance (più veloce su file grandi)",
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
        "--tests", default=None,
        help="File JSON con i casi di test (default: <originale>.tests.json se esiste)",
    )
    parser.add_argument(
        "--json", action="store_true",
        help="Emette i risultati anche in formato JSON su stdout",
    )
    args = parser.parse_args()

    for path in (args.original, args.decompiled):
        if not os.path.isfile(path):
            print(f"[ERRORE] File non trovato: {path}", file=sys.stderr)
            sys.exit(1)

    # --- Lettura testi grezzi ---
    with open(args.original,   "r", encoding="utf-8", errors="replace") as f:
        text_orig = f.read()
    with open(args.decompiled, "r", encoding="utf-8", errors="replace") as f:
        text_dec = f.read()

    # 1. Re-executability
    can_compile, compile_err = check_reexecutability(args.decompiled)

    # 1b. Functional Match
    functional = None
    asan = None
    cases = load_test_cases(args.original, args.tests)
    if not args.no_functional:
        functional = functional_test(args.original, args.decompiled, cases)
    if not args.no_asan and can_compile:
        asan = asan_test(args.original, args.decompiled, cases)

    # Errori di build per categoria: dalla compilazione, oppure dal link se
    # la compilazione è riuscita ma il test funzionale non ha potuto linkare
    if not can_compile:
        error_categories = classify_compiler_errors(compile_err)
    elif functional and functional["build_stderr"]:
        error_categories = classify_compiler_errors(functional["build_stderr"])
    else:
        error_categories = {}

    # 2. Edit Similarity
    es = edit_similarity(text_orig, text_dec)

    # 3 & 4. Parsing AST
    ted_raw = float("nan")
    ted_norm = float("nan")
    col_orig = ASTCollector()
    col_dec  = ASTCollector()
    ast_error = None

    try:
        ast_orig = parse_c_file(args.original)
        ast_dec  = parse_c_file(args.decompiled)

        col_orig.visit(ast_orig)
        col_dec.visit(ast_dec)

        # 4. Tree Edit Distance
        if not args.no_ted and ZSS_AVAILABLE:
            ted_raw, ted_norm = tree_edit_distance(ast_orig, ast_dec)

    except Exception as exc:
        ast_error = str(exc)
        print(f"\n[ATTENZIONE] Parsing AST fallito: {exc}", file=sys.stderr)
        print("  Le metriche AST non saranno disponibili.\n", file=sys.stderr)

    # 3. Histogram similarity
    histo_sim  = node_histogram_similarity(col_orig, col_dec) if not ast_error else float("nan")
    fanout_sim = fanout_similarity(col_orig, col_dec)         if not ast_error else float("nan")
    profile    = structural_profile_diff(col_orig, col_dec)   if not ast_error else {}

    extra = {
        "error_categories": error_categories,
        "asan": asan,
        "size": {
            "loc_orig":   count_loc(text_orig),
            "loc_dec":    count_loc(text_dec),
            "funcs_orig": None if ast_error else col_orig.node_counts.get("FuncDef", 0),
            "funcs_dec":  None if ast_error else col_dec.node_counts.get("FuncDef", 0),
        },
    }

    # --- Output testuale ---
    if not args.json:
        print_report(
            args.original, args.decompiled,
            can_compile, compile_err,
            functional,
            es,
            histo_sim,
            ted_raw, ted_norm,
            col_orig, col_dec,
            fanout_sim,
            profile,
            extra,
        )
    else:
        # Con --json stampa il report su stderr e JSON su stdout
        import sys as _sys
        _old = _sys.stdout
        _sys.stdout = _sys.stderr
        print_report(
            args.original, args.decompiled,
            can_compile, compile_err,
            functional,
            es,
            histo_sim,
            ted_raw, ted_norm,
            col_orig, col_dec,
            fanout_sim,
            profile,
            extra,
        )
        _sys.stdout = _old

    # --- Output JSON opzionale ---
    if args.json:
        import json
        result = {
            "files": {
                "original":   args.original,
                "decompiled": args.decompiled,
            },
            "re_executability": {
                "success": can_compile,
                "error":   compile_err if not can_compile else None,
                "error_categories": error_categories,
            },
            "functional": functional,
            "asan": asan,
            "size": extra["size"],
            "edit_similarity_pct": round(es, 2),
            "ast_node_histogram_similarity_pct": round(histo_sim, 2) if not math.isnan(histo_sim) else None,
            "tree_edit_distance": {
                "raw":        None if math.isnan(ted_raw)  else int(ted_raw),
                "similarity_pct": None if math.isnan(ted_norm) else round(ted_norm * 100, 2),
            },
            "ast_depth": {
                "original":   col_orig.max_depth,
                "decompiled": col_dec.max_depth,
                "delta":      col_dec.max_depth - col_orig.max_depth,
            },
            "fanout_similarity_pct": round(fanout_sim, 2) if not math.isnan(fanout_sim) else None,
            "structural_profile":   profile,
            "ast_error":            ast_error,
        }
        print(json.dumps(result, indent=2, ensure_ascii=False))


if __name__ == "__main__":
    main()
