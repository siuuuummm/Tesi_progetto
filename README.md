# Fedeltà alle vulnerabilità nella decompilazione con LLM

Codice, benchmark e risultati della tesi di laurea triennale in Informatica
*Valutazione Comparativa di LLM per la Decompilazione* (Università degli Studi di
Torino, a.a. 2025/2026, candidato Filippo Bonino, relatore prof. Idilio Drago).

La tesi misura se le ricostruzioni prodotte da una pipeline agentica di
decompilazione conservano le vulnerabilità di memoria del binario o tendono a
"correggerle". Un modello linguistico, guidato dall'agente
[Goose](https://github.com/block/goose), interroga Ghidra in modalità headless
tramite il Model Context Protocol e ricostruisce il sorgente C di un binario
privato dei simboli; la ricostruzione viene poi confrontata con il programma
originale tramite AddressSanitizer e test funzionali.

## Contenuto

```
.
├── GhidraMCP-release-1-4/          bridge MCP di GhidraMCP (invariato) e server headless scritto per la tesi
│   ├── bridge_mcp_ghidra.py        bridge MCP del progetto GhidraMCP 1.4
│   ├── ghidra_mcp_server.py        script Jython: server HTTP dentro Ghidra headless
│   └── ghidra-mcp                  avvio del bridge come estensione di Goose
├── config/
│   ├── requirements-container.txt  dipendenze Python
│   └── goose-config.yaml           esempio di configurazione di Goose (senza chiavi)
└── Programs/Experiments/
    ├── Python AST controller/      pipeline, metriche e risultati
    │   ├── auto_pipeline.py        compilazione, stripping, Ghidra + Goose, metadati
    │   ├── ast_analyzer.py         metriche: compilabilità, test funzionali, AddressSanitizer
    │   ├── run_benchmark.py        analizza tutte le ricostruzioni e scrive il CSV
    │   ├── check_binary.py         confronta il comportamento dell'originale da O1 a O3 con O0
    │   ├── NOTE_BENCHMARK.md       registro delle decisioni di progetto
    │   ├── originals/              i cinque programmi vulnerabili e i loro casi di test
    │   ├── risultati_finali.csv    una riga per sessione (risultati della tesi)
    │   ├── <modello>/              ricostruzioni nella condizione standard
    │   ├── <modello>__senza_divieto/  ricostruzioni nella condizione di controllo
    │   └── Archivio1/ 2/ 3/        prove preliminari, non usate nei risultati
    └── Secfocus/Eseguibili/<programma>/
        └── goose_<modello>_<livello>_run<n>.log   log completo di ogni sessione
```

### Programmi del benchmark

| Programma | Vulnerabilità | Rilevamento |
|---|---|---|
| `cwe119.c` | `strcpy` in un buffer sullo stack | AddressSanitizer |
| `cwe134.c` | stringa dell'utente come formato di `printf` | output del programma |
| `cwe190.c` | dimensione troncata a 8 bit, poi overflow sullo heap | AddressSanitizer |
| `cwe193.c` | errore di uno nel controllo della lunghezza | AddressSanitizer |
| `cwe416.c` | uso della sessione dopo il logout | AddressSanitizer |

Ogni programma ha un file `<nome>.tests.json` con i casi di test; quelli marcati
`"trigger": true` attivano la vulnerabilità.

### Modelli e condizioni

| Cartella | Modello | Esecuzione |
|---|---|---|
| `Qwen3.8-27b` | Qwen3.8-27B | OpenRouter, fornitore Phala |
| `mimo-v2.6-flash_ionet_fp8` | MiMo-V2.6-Flash | OpenRouter, fornitore io.net, fp8 |
| `gemma4-26b-a4b-Q4_k_xl` | Gemma 4 26B-A4B | locale, llama.cpp, Unsloth UD-Q4_K_XL |

Ogni modello è valutato in due condizioni: con il prompt standard, che vieta di
correggere i difetti, e con una variante di controllo senza quel divieto
(cartelle con suffisso `__senza_divieto`). Il prompt usato è registrato in ogni
`.meta.json` con la sua impronta SHA-256 (`0f327dfcc92e` standard,
`c06a2621c537` senza divieto).

## Formato dei risultati

Per ogni sessione la cartella del modello contiene:

- `<programma>_<livello>_llm[_<n>].c`: la ricostruzione (`_<n>` è l'indice
  dell'esecuzione, assente per la prima);
- `<programma>_<livello>_llm[_<n>].meta.json`: esito, durata, solleciti,
  impronta del prompt, percorso del log, accessi fuori dalla cartella di lavoro.

Le colonne principali di `risultati_finali.csv` sono:

| Colonna | Significato |
|---|---|
| `esito` | `ok`, oppure il motivo per cui manca la ricostruzione (`nessun_output`, `timeout`, `errore_fornitore`, …) |
| `re_executability` | 1 se la ricostruzione compila (`gcc -c`; nella tesi "compilabilità") |
| `vuln_conservata` | 1 se la vulnerabilità è conservata sui casi di attivazione |
| `errore_aggiunto` | 1 se compare un errore di memoria su un caso innocuo |
| `pass_innocui`, `pass_attivazione` | percentuale di casi superati, separata per tipo |
| `functional_pass_rate` | percentuale di casi superati su tutti i casi |

Le colonne di similarità testuale e strutturale (`edit_similarity`, `ast_*`,
`tree_edit_distance`, …) sono calcolate ma non usate nella tesi.

### Corrispondenza con la tesi

La tesi conta le prime tre esecuzioni valide di ogni configurazione. Rispetto al
CSV ci sono tre differenze, tutte motivate nella tesi:

- le sessioni di Qwen3.8-27b su `cwe416` dell'11 ottobre 2026 sono attribuite a
  un problema del fornitore e sostituite da quelle del 12 ottobre;
- le sessioni di Qwen3.8-27b nella condizione di controllo su `cwe193` rifatte il
  15 ottobre si trovano in `Qwen3.8-27b__senza_divieto__senza_divieto/` (il nome
  del modello era stato passato già con il suffisso) e appartengono alla
  condizione di controllo;
- la sessione `mimo-v2.6-flash_ionet_fp8__senza_divieto/cwe119_O0_llm_2` è esclusa
  perché il modello cerca il sorgente nel filesystem e il log non permette di
  verificare cosa abbia letto.

## Rieseguire gli esperimenti

Requisiti: Linux x86-64, GCC con AddressSanitizer, `bwrap` e `stdbuf`,
[Ghidra 11.3.2](https://github.com/NationalSecurityAgency/ghidra/releases)
(non incluso: va scaricato ed estratto in `ghidra_11.3.2_PUBLIC/`), Goose 1.29.1
configurato con il fornitore del modello, Python 3 con le dipendenze di
`config/requirements-container.txt`.

Il percorso della radice si imposta con la variabile `TESI_ROOT` (altrimenti vale
quello del computer dell'autore). Dalla cartella `Programs/Experiments/Python AST controller`:

```bash
# una sessione per ogni livello di ottimizzazione, condizione standard
python3 auto_pipeline.py --source originals/cwe119.c --model Qwen3.8-27b --run 1

# condizione di controllo: passare il nome del modello senza suffisso
python3 auto_pipeline.py --source originals/cwe119.c --model Qwen3.8-27b --run 1 --senza-divieto

# rifare solo le sessioni mancanti o fallite per cause esterne
python3 auto_pipeline.py --source originals/cwe119.c --model Qwen3.8-27b --run 2 --solo-mancanti

# analizzare tutte le ricostruzioni e aggiornare il CSV
python3 run_benchmark.py --root . --out risultati_finali.csv
```

Le chiavi dei fornitori restano nella configurazione di Goose (portachiavi di
sistema) e non sono nel repository. La generazione non è deterministica: una
nuova esecuzione produce ricostruzioni diverse da quelle salvate qui.

## Prove preliminari

`Archivio1/`, `Archivio2/` e `Archivio3/` contengono le prove fatte prima di
fissare la configurazione dell'esperimento (maggio–ottobre 2026), con altri
modelli, altri programmi e versioni precedenti del prompt e della pipeline. Non
sono usate nei risultati della tesi.
