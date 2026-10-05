import os
import subprocess
import time
from pathlib import Path

# --- CONFIGURAZIONE ---
GHIDRA_PATH = "/var/home/pippo/Desktop/Universita/Tesi/ghidra_11.3.2_PUBLIC"
ANALYZE_HEADLESS = f"{GHIDRA_PATH}/support/analyzeHeadless"
GHIDRA_SERVER_SCRIPT = "/var/home/pippo/Desktop/Universita/Tesi/GhidraMCP-release-1-4/ghidra_mcp_server.py"
GOOSE_BIN = "/var/home/pippo/.local/bin/goose"

def kill_port_8080():
    try: subprocess.run(["fuser", "-k", "8080/tcp"], capture_output=True)
    except: pass

def main():
    import sys
    if len(sys.argv) < 2: return
    
    source_file = Path(sys.argv[1]).resolve()
    base_name = source_file.stem
    output_dir = source_file.parent / "Eseguibili"
    output_dir.mkdir(exist_ok=True)
    
    exe_file = output_dir / f"{base_name}_bin"
    llm_output = output_dir / f"{base_name}_llm.c"
    
    # --- NUOVI FILE DI LOG ---
    ghidra_log_path = output_dir / f"{base_name}_ghidra.log"
    goose_log_path = output_dir / f"{base_name}_goose.log"
    
    # Pulizia preliminare del file di output
    if llm_output.exists(): llm_output.unlink()

    # 1. Compila e Strip
    print("[*] Compilazione...")
    subprocess.run(["gcc", "-O0", str(source_file), "-o", str(exe_file), "-lm"], check=True)
    subprocess.run(["strip", str(exe_file)], check=True)

    # 2. Reset Porta
    kill_port_8080()

    # 3. Avvio Ghidra Headless in background con LOGGING
    project_dir = Path("/tmp/ghidra_automation")
    project_dir.mkdir(exist_ok=True)
    project_name = f"Proj_{int(time.time())}"

    print(f"[*] Avvio analisi su {base_name}. I log di Ghidra sono su {ghidra_log_path.name}")
    ghidra_cmd = [ANALYZE_HEADLESS, str(project_dir), project_name, "-import", str(exe_file), "-postScript", GHIDRA_SERVER_SCRIPT, "-overwrite"]
    
    # APRIAMO IL FILE DI LOG PER GHIDRA (anziché DEVNULL)
    with open(ghidra_log_path, "w") as ghidra_log:
        process = subprocess.Popen(ghidra_cmd, stdout=ghidra_log, stderr=subprocess.STDOUT)
    
    time.sleep(6) # Tempo per alzare il server Java

    # 4. Prompt forzato per Goose
    instruction = (
        "Sei un esperto di Reverse Engineering. La tua missione è ricostruire il sorgente C di un binario STRIPPED.\n\n"
        "OPERAZIONI RICHIESTE:\n"
        "1. Analizza l'Entry Point (0x4003b0) usando 'disassemble_function'.\n"
        "2. Identifica la chiamata a '__libc_start_main'. Il primo argomento passato a questa funzione è l'indirizzo del 'main'.\n"
        "3. Vai all'indirizzo del 'main' trovato, usa 'decompile_function' e analizza l'algoritmo.\n"
        "4. Se il 'main' chiama altre funzioni interne (es. FUN_0040...), esamina anche quelle per capire l'intera logica.\n\n"
        "REGOLE DI OUTPUT:\n"
        "- Produci un codice C completo, leggibile e autonomo.\n"
        "- Sostituisci i tipi di Ghidra (undefined8, byte, ecc.) con tipi C standard (int, char, ecc.).\n"
        f"- SALVA IL RISULTATO FINALE nel file: {llm_output} usando il tool 'write_file'.\n\n"
        "IMPORTANTE: Se riscontri un errore '500' dal server, non fermarti. Prova a usare 'list_functions' "
        "o 'list_strings' per orientarti e ritentare la decompilazione. Non chiudere la sessione finché il file non è stato scritto."
    )
    
    print(f"[*] Avvio Goose. I log di Goose verranno salvati su {goose_log_path.name}")
    try:
        # Aggiungiamo un flag --retries (se supportato) o specifichiamo il system/developer agent
        # env = os.environ.copy()
        # env['GOOSE_TEMPERATURE'] = '0' # Opzionale, per fissare i prompt
        subprocess.run([GOOSE_BIN, "run", "--text", instruction], check=True)
               
        # VERIFICA REALE
        if llm_output.exists() and llm_output.stat().st_size > 10:
            print(f"\n[+++] MISSIONE COMPIUTA: {llm_output} creato ({llm_output.stat().st_size} bytes)")
        else:
            print(f"\n[!!!] FALLIMENTO: Goose non ha scritto il file. Controlla {goose_log_path.name} e {ghidra_log_path.name}.")
            
    except subprocess.CalledProcessError as e:
        print(f"\n[!!!] ERRORE: Goose è crashato. Log salvati in {goose_log_path.name}")
    finally:
        process.terminate()
        kill_port_8080()

if __name__ == "__main__":
    main()