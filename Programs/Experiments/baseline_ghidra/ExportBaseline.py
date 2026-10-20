# Esporta il decompilato di Ghidra del main e delle funzioni raggiungibili da esso.
# @runtime Jython
import re
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor

out = getScriptArgs()[0]
mon = ConsoleTaskMonitor()
ifc = DecompInterface()
ifc.openProgram(currentProgram)
fm = currentProgram.getFunctionManager()

def dec(f):
    r = ifc.decompileFunction(f, 120, mon)
    d = r.getDecompiledFunction() if r else None
    return d.getC() if d else None

byname = {}
for f in fm.getFunctions(True):
    byname[f.getName()] = f
ecode = dec(byname["entry"])
m = re.search(r"libc_start_main[^(]*\(\s*(?:\([^)]*\)\s*)?(\w+)", ecode)
if m is None:
    open(out, "w").write("// main non trovato\n" + ecode)
    exit()
main = byname[m.group(1)]
seen, todo = [], [main]
while todo:
    f = todo.pop(0)
    if f in seen or f.isExternal() or f.isThunk():
        continue
    seen.append(f)
    for g in f.getCalledFunctions(mon):
        todo.append(g)
fh = open(out, "w")
fh.write("// main: %s\n" % main.getName())
for f in seen:
    fh.write(dec(f) + "\n")
fh.close()
