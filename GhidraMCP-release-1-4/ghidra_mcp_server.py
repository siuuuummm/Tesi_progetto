# -*- coding: utf-8 -*-
# @category MCP
# @runtime Jython

from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import urlparse
import traceback
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
# ... (altri import)

def find_function_by_name(name):
    for f in currentProgram.getFunctionManager().getFunctions(True):
        if f.getName() == name:
            return f
    return None

def decompile(func):
    if func is None:
        return "// Errore: Funzione non trovata o parametri mancanti."
    ifc = DecompInterface()
    ifc.openProgram(currentProgram)
    res = ifc.decompileFunction(func, 0, ConsoleTaskMonitor())
    if res is None:
        return "// Errore: Risultato decompiler nullo."
    decomp_func = res.getDecompiledFunction()
    if decomp_func is None:
        return "// Errore: Output decompiler nullo."
    return decomp_func.getC()

class GhidraHandler(BaseHTTPRequestHandler):
    def reply(self, code, text):
        self.send_response(code)
        self.send_header('Content-Type', 'text/plain; charset=utf-8')
        self.end_headers()
        self.wfile.write(text.encode('utf-8'))

    # Il bridge usa POST solo per la decompilazione per nome e per le
    # operazioni di modifica (rinomine, commenti, tipi): qui serve solo la prima.
    def do_POST(self):
        try:
            endpoint = urlparse.urlparse(self.path).path.strip('/')
            length = int(self.headers.getheader('content-length') or 0)
            body = self.rfile.read(length).decode('utf-8').strip()
            print("[MCP POST] " + endpoint + " " + body)
            if endpoint == "decompile":
                self.reply(200, decompile(find_function_by_name(body)))
            else:
                self.reply(404, "Operazione non supportata dal server headless: " + endpoint)
        except Exception as e:
            print("[MCP ERROR] " + str(e))
            traceback.print_exc()
            self.reply(500, "Errore Interno: " + str(e))

    def do_GET(self):
        try:
            parsed_path = urlparse.urlparse(self.path)
            params = urlparse.parse_qs(parsed_path.query)
            endpoint = parsed_path.path.strip('/')
            
            print("[MCP REQUEST] " + endpoint + " " + str(params))
            output_list = []
            
            # --- MEMORIA E IMPORT ---
            if endpoint in ["segments", "list_segments"]:
                blocks = currentProgram.getMemory().getBlocks()
                for b in blocks:
                    output_list.append(b.getName() + " [" + b.getStart().toString() + " - " + b.getEnd().toString() + "]")
            
            elif endpoint in ["imports", "list_imports"]:
                imports = currentProgram.getSymbolTable().getExternalSymbols()
                for sym in imports:
                    output_list.append(sym.getName() + " @ " + sym.getAddress().toString())
                    
            elif endpoint in ["searchFunctions", "search_functions"]:
                query = params.get('query', [''])[0]
                # Cerca nelle funzioni interne
                fm = currentProgram.getFunctionManager()
                for func in fm.getFunctions(True):
                    if query in func.getName():
                        output_list.append(func.getName() + " @ " + func.getEntryPoint().toString())
                # Cerca anche nei simboli esterni (es. puts, printf)
                for sym in currentProgram.getSymbolTable().getExternalSymbols():
                    if query in sym.getName():
                        output_list.append("[EXT] " + sym.getName() + " @ " + sym.getAddress().toString())

            elif endpoint == "list_functions":
                fm = currentProgram.getFunctionManager()
                for func in fm.getFunctions(True):
                    output_list.append(func.getName())

            # --- DECOMPILAZIONE ---
            elif endpoint in ["decompile_function", "get_function_by_address"]:
                addr_str = params.get('address', [None])[0]
                name_str = params.get('name', [None])[0]
                
                func = None
                # Se Goose ci dà il nome invece dell'indirizzo
                if name_str:
                    func = find_function_by_name(name_str)

                # Se Goose ci dà l'indirizzo
                elif addr_str:
                    addr = currentProgram.getAddressFactory().getAddress(addr_str)
                    if addr:
                        func = getFunctionAt(addr)
                        if func is None:
                            createFunction(addr, "FUN_" + addr_str)
                            func = getFunctionAt(addr)
                
                output_list.append(decompile(func))

            # --- ASSEMBLY PURE ---
            elif endpoint == "disassemble_function":
                addr_str = params.get('address', [None])[0]
                if addr_str:
                    addr = currentProgram.getAddressFactory().getAddress(addr_str)
                    if addr:
                        listing = currentProgram.getListing()
                        func = getFunctionContaining(addr)
                        if func is not None:
                            # tutta la funzione, non solo le prime istruzioni
                            for ins in listing.getInstructions(func.getBody(), True):
                                output_list.append(ins.getAddress().toString() + ": " + ins.toString())
                        else:
                            code_units = listing.getCodeUnits(addr, True)
                            for i in range(200):
                                if code_units.hasNext():
                                    cu = code_units.next()
                                    output_list.append(cu.getAddress().toString() + ": " + cu.toString())
            
            # --- STRINGHE E RIFERIMENTI (Quelli che bloccavano Goose!) ---
            elif endpoint in ["strings", "list_strings"]:
                filter_str = params.get('filter', [''])[0]
                data_it = currentProgram.getListing().getData(True)
                count = 0
                for d in data_it:
                    if count > 100: break # Evita di impallare il server con troppe stringhe
                    if d.isDefined() and "String" in d.getDataType().getName():
                        val = str(d.getValue())
                        if filter_str in val or filter_str == '':
                            output_list.append(d.getAddress().toString() + ": " + val)
                            count += 1
                            
            # --- RIFERIMENTI INCROCIATI (XREFS) ---
            elif endpoint in ["function_xrefs", "get_xrefs_to", "xrefs_to"]:
                name = params.get('name', [''])[0]
                addr_str = params.get('address', [''])[0]
                
                target_addrs = []
                if addr_str:
                    a = currentProgram.getAddressFactory().getAddress(addr_str)
                    if a: target_addrs.append(a)
                elif name:
                    # Raccogliamo in modo sicuro gli indirizzi (evitando crash su simboli strani)
                    for sym in currentProgram.getSymbolTable().getSymbols(name):
                        if sym is not None and sym.getAddress() is not None:
                            target_addrs.append(sym.getAddress())
                
                ref_mgr = currentProgram.getReferenceManager()
                for a in target_addrs:
                    refs = ref_mgr.getReferencesTo(a)
                    for ref in refs:
                        try:
                            f_addr = ref.getFromAddress()
                            t_addr = ref.getToAddress()
                            output_list.append("Chiamata da: " + f_addr.toString() + " a " + t_addr.toString())
                        except:
                            pass # Ignoriamo silenziosamente eventuali ref non leggibili

            elif endpoint == "xrefs_from":
                addr_str = params.get('address', [''])[0]
                a = currentProgram.getAddressFactory().getAddress(addr_str) if addr_str else None
                if a:
                    for ref in currentProgram.getReferenceManager().getReferencesFrom(a):
                        output_list.append("Riferimento da: " + ref.getFromAddress().toString() + " a " + ref.getToAddress().toString())

            # --- OPERAZIONI NON IMPLEMENTATE ---
            # Errore esplicito invece di una risposta vuota, che il modello
            # leggerebbe come "nessun dato".
            else:
                self.reply(404, "Operazione non supportata dal server headless: " + endpoint)
                return

            # --- RISPOSTA ---
            self.reply(200, "\n".join(output_list))

        except Exception as e:
            print("[MCP ERROR] " + str(e))
            traceback.print_exc()
            self.reply(500, "Errore Interno: " + str(e))

def run(port=8080):
    server_address = ('127.0.0.1', port)
    httpd = HTTPServer(server_address, GhidraHandler)
    print("Server Ghidra MCP attivo sulla porta " + str(port))
    httpd.serve_forever()

if __name__ == "__main__":
    run()