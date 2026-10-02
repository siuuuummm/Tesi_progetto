# -*- coding: utf-8 -*-
# @category MCP
# @runtime Jython

from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import urlparse
import traceback
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
# ... (altri import)
import time

class GhidraHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # LIMITATORE RPM: Forza un'attesa di 4.5 secondi per richiesta
        # Questo evita il blocco di Google AI Studio (15 RPM)
        time.sleep(4.5) 
        
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
                    funcs = currentProgram.getFunctionManager().getFunctions(True)
                    for f in funcs:
                        if f.getName() == name_str:
                            func = f
                            break
                            
                # Se Goose ci dà l'indirizzo
                elif addr_str:
                    addr = currentProgram.getAddressFactory().getAddress(addr_str)
                    if addr:
                        func = getFunctionAt(addr)
                        if func is None:
                            createFunction(addr, "FUN_" + addr_str)
                            func = getFunctionAt(addr)
                
                if func:
                    ifc = DecompInterface()
                    ifc.openProgram(currentProgram)
                    res = ifc.decompileFunction(func, 0, ConsoleTaskMonitor())
                    if res is not None:
                        decomp_func = res.getDecompiledFunction()
                        if decomp_func is not None:
                            output_list.append(decomp_func.getC())
                        else:
                            output_list.append("// Errore: Output decompiler nullo.")
                    else:
                        output_list.append("// Errore: Risultato decompiler nullo.")
                else:
                    output_list.append("// Errore: Funzione non trovata o parametri mancanti.")

            # --- ASSEMBLY PURE ---
            elif endpoint == "disassemble_function":
                addr_str = params.get('address', [None])[0]
                if addr_str:
                    addr = currentProgram.getAddressFactory().getAddress(addr_str)
                    if addr:
                        listing = currentProgram.getListing()
                        code_units = listing.getCodeUnits(addr, True)
                        for i in range(30):
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
            elif endpoint in ["function_xrefs", "get_xrefs_to"]:
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

            # --- RISPOSTA ---
            self.send_response(200)
            self.send_header('Content-Type', 'text/plain; charset=utf-8')
            self.end_headers()
            self.wfile.write("\n".join(output_list).encode('utf-8'))
            
        except Exception as e:
            print("[MCP ERROR] " + str(e))
            traceback.print_exc()
            self.send_response(500)
            self.send_header('Content-Type', 'text/plain')
            self.end_headers()
            self.wfile.write("Errore Interno: " + str(e))

def run(port=8080):
    server_address = ('127.0.0.1', port)
    httpd = HTTPServer(server_address, GhidraHandler)
    print("Server Ghidra MCP attivo sulla porta " + str(port))
    httpd.serve_forever()

if __name__ == "__main__":
    run()