# Note sul benchmark di decompilazione LLM

Questo documento riassume le modifiche fatte alla pipeline di benchmark e il motivo di ciascuna.
Copre la revisione degli script, il confronto con i paper di riferimento e le verifiche aggiunte.

Ultimo aggiornamento: 5 ottobre 2026.

---

## 1. Il progetto in breve

Il banco di prova misura quanto bene un LLM ricostruisce il codice C a partire da un binario strippato.
Il modello lavora in modo agentico: interroga Ghidra tramite MCP attraverso Goose.

| File | Ruolo |
|---|---|
| `auto_pipeline.py` | Per ogni sorgente e livello O0–O3: compila, fa lo strip, avvia Ghidra headless con il server MCP, lancia Goose con il prompt, salva il `.c` prodotto, aggiorna il CSV |
| `ast_analyzer.py` | Confronta un sorgente originale con la sua ricostruzione (vedi §5) |
| `run_benchmark.py` | Esegue `ast_analyzer` su tutte le cartelle dei modelli e scrive un CSV, con una riga per funzione × modello × livello × variante |
| `originals/` | Sorgenti di riferimento ed eventuali file `<nome>.tests.json` con i casi di test |
| `Archivio1/`, `Archivio2/` | Run precedenti (vedi §3.3) |

---

## 2. Problemi trovati nella revisione iniziale

Prima di modificare qualcosa ho riletto gli script e i log di Goose. Questi erano i problemi che rendevano i numeri difficili da difendere in una tesi:

1. **Il modello poteva vedere file che non doveva vedere.** Goose ha l'estensione `developer` (shell e lettura file) e lavorava dentro `Secfocus/`, dove si trovano anche i sorgenti originali. I log mostravano `find .../Secfocus`, letture dei log di Ghidra e dei log delle sessioni precedenti. In `tea_cipher/goose_O0_run2.log` il modello è andato a cercare l'output del run 1, quindi il run 2 non era indipendente. Inoltre il percorso di output nel prompt (`.../cwe119/cwe119_O0_llm.c`) rivelava il nome del programma.
2. **La "re-executability" misurava solo la compilazione.** `gcc -c` non esegue nulla, mentre nei paper la re-executability significa che il programma supera i test. Un file che compila ma fa tutt'altro prendeva comunque 1.
3. **Le metriche AST non vedono la semantica.** Nel TED e nell'istogramma le etichette sono solo il tipo di nodo: `a + b` e `a - b` risultano identici e una costante sbagliata non pesa. *Non ancora sistemato, vedi §8.*
4. **I solleciti aprivano una sessione nuova.** Ogni `goose run` partiva da zero, quindi il sollecito "scrivi il codice che hai già ricostruito" arrivava a un modello senza contesto.
5. **Problemi minori:** attesa fissa di 8 s per l'avvio di Ghidra, `current_model` scritto a mano nel CONFIG, deduplica contorta in `run_benchmark.py`, metrica di fan-out poco discriminante (sempre tra 83 e 100%), "score medio" che media metriche eterogenee.

---

## 3. Modifiche alla pipeline (`auto_pipeline.py`)

### 3.1 Sandbox per Goose

**Cosa.**
- Ogni sessione gira in una cartella temporanea `/tmp/re_task_XXXX/` che contiene solo il binario. Goose viene lanciato con quella cartella come directory di lavoro e deve scrivere `out.c`.
- I log di Ghidra e Goose restano in `Secfocus/Eseguibili/<nome>/`, fuori dalla sandbox. La sandbox viene cancellata a fine run e una copia del binario resta nei log.
- Dopo ogni run, `find_sandbox_violations()` analizza il log di Goose (righe `command:` e `path:`) e segnala gli accessi alla home, alle cartelle del benchmark, i percorsi con `..` e i comandi su `/`.
- Ogni run salva un file `<variante>.meta.json` accanto al `.c` con: sorgente, modello, livello, run, timestamp, durata, solleciti usati, nome della sessione Goose, hash del prompt e violazioni.

**Perché.** Senza isolamento non si può escludere che il modello abbia letto il sorgente o l'output di un run precedente: i numeri non sarebbero validi. Il percorso neutro (`out.c`) toglie anche l'indizio del nome del programma.

**Limite.** È un controllo, non un vero isolamento: Goose può ancora leggere la home se usa un percorso assoluto, ma ora lo vedi nei log e nella colonna `sandbox_violations`. Per bloccarlo davvero bisognerebbe far girare Goose dentro `bwrap` o in un container. Il rilevatore guarda solo la prima riga di ogni comando.

**Verifica.** Su un log simulato le operazioni lecite dentro la sandbox non vengono segnalate, mentre `ls ..`, `find /` e `cat ~/…/koch.c` sì. Sui log vecchi segnala 9 log su 54.

### 3.2 Solleciti nella stessa sessione

**Cosa.** Il primo tentativo usa `goose run --name <nome sandbox>`. I solleciti usano `--name <nome sandbox> --resume`. Il nome è quello casuale della sandbox, quindi unico e senza informazioni sul programma. Il numero di solleciti usati finisce nel `.meta.json`.

**Perché.** Prima ogni sollecito apriva una sessione vuota e il modello non sapeva cosa aveva già decompilato. Il numero di solleciti è anche un dato utile per la tesi: quanto spesso un modello si ferma senza scrivere il file.

**Verifica.** Con il server reale ho mandato due messaggi brevi, il secondo con `--resume`: il modello ha ricordato la parola del primo. Con un finto `goose` ho verificato il flusso completo: prima chiamata senza `--resume`, solleciti con `--resume` e stesso nome, tutte lanciate dalla sandbox.

**Limite.** Se il primo tentativo va in timeout (1300 s), Goose viene interrotto bruscamente. Non è verificato che l'ultimo messaggio a metà venga salvato.

### 3.3 Pulizia dei run precedenti

**Cosa.** I risultati vecchi sono stati spostati, non cancellati, in `Archivio2/`: le cartelle `gemma4-12b-Q6/` e `Qwythos-9b/`, `results.csv`, `ResultNewPrompt.csv`, `DONE` e tutta `Secfocus/Eseguibili/`. Ho rimosso `/tmp/ghidra_auto/` e la cartella vuota `Qwen3.6-35b-a3b/`. `run_benchmark.py` ora ignora le cartelle `Archivio*`.

**Perché.** I run vecchi sono stati prodotti senza sandbox e con un prompt diverso, quindi non sono confrontabili con i nuovi. Restano però consultabili per la tesi.

### 3.3b Rimosso il ritardo nel server Ghidra (5 ottobre 2026)

**Cosa.** `GhidraMCP-release-1-4/ghidra_mcp_server.py` aspettava 4,5 s a ogni richiesta (`time.sleep(4.5)`). Il ritardo è stato tolto.

**Perché.** Serviva solo a rispettare il limite di 15 richieste al minuto dei modelli gratuiti di Google AI Studio. I modelli locali non hanno limiti e quelli grandi sono a pagamento. Il ritardo gonfiava la durata delle sessioni (da 50 a 225 s per 11–50 chiamate) e consumava il tempo massimo di 1300 s, causando probabilmente dei timeout a O3.

**Conseguenza.** Le sessioni di `Test_v3.csv` sono state eseguite *con* il ritardo. Le metriche di fedeltà e di correttezza restano valide; le durate, i timeout e i solleciti di quelle sessioni non sono invece confrontabili con le sessioni nuove.

### 3.3c Log con il nome del modello (5 ottobre 2026)

**Cosa.** I log ora si chiamano `goose_<modello>_<livello>_run<n>.log` e `ghidra_<modello>_<livello>_run<n>.log`, in `Secfocus/Eseguibili/<programma>/`. I caratteri non validi nel nome del modello diventano `_` (es. `qwen/qwen3.8-27b` → `qwen_qwen3.8-27b`).

**Perché.** Prima il nome dipendeva solo da programma, livello ed esecuzione: ogni modello sovrascriveva i log del modello precedente (23 log su 52 erano condivisi). Senza log non si possono verificare le violazioni della sandbox, contare le autoverifiche né classificare i casi in cui la vulnerabilità sparisce.

**Conseguenza.** Per le sessioni precedenti al 5 ottobre resta solo il log dell'ultimo modello eseguito su ciascun programma e livello. Il modello a cui appartiene un log vecchio si ricava dall'intestazione (`new session · <fornitore> <modello>`).

### 3.4 Modifiche al prompt

| Modifica | Perché |
|---|---|
| L'esempio *"Se il decompilato mostra 0x9e3779b9…"* è diventato `0x1a2b3c4d` | `0x9E3779B9` è proprio il delta di TEA e la costante di feistel: su quei programmi il prompt suggeriva la risposta. `0x1a2b3c4d` non compare in nessun sorgente |
| Nuovo divieto: *"VIETATO correggere bug, overflow, chiamate insicure (strcpy, gets, sprintf, printf con formato non costante...) o controlli mancanti, anche se evidenti…"* | Ricostruire un binario serve anche a trovarne le vulnerabilità: una ricostruzione che corregge il bug la nasconde. I modelli sono addestrati a essere utili e tendono a "sistemare" il codice da soli, quindi va chiesto in modo esplicito (vedi §6) |

Hash del prompt attuale (`prompt_sha256` nei `.meta.json`): **`55a8eac74ed6`**. Usalo nella tesi per indicare la versione del prompt.

---

## 4. Confronto con i paper di riferimento

I paper in `Tesi/Paper/` sono:
- **LLM4Decompile** (Tan et al., EMNLP 2024): modelli addestrati per decompilare; metriche re-executability ed Edit Similarity; benchmark HumanEval-Decompile.
- **DecLLM** (Wong et al., ISSTA 2025): ciclo iterativo di riparazione con errori del compilatore, confronto dell'output e ASan; fuzzing; applicazione a CodeQL.

### Cosa è già allineato
- Scenario realistico: binari strippati, gcc su x86 Linux, livelli O0–O3, Ghidra come decompilatore. È lo scenario che LLM4Decompile difende nell'Appendice A.
- Nella classificazione dei paper l'approccio è un **Refined-Decompile**, perché l'LLM lavora sull'output di Ghidra. È però **agentico**: il modello interroga Ghidra via MCP invece di ricevere lo pseudocodice in un solo prompt. Nessuno dei due paper fa questo, quindi è il contributo originale della tesi.
- Le metriche strutturali AST vanno oltre la sola Edit Similarity, che LLM4Decompile stesso definisce "difficile da interpretare".
- Il test funzionale (§5.1) corrisponde alla metrica centrale di entrambi i paper.

### Decisioni prese
- **Per ora si misura solo il primo tentativo, senza ciclo di feedback.** Il ciclo con errori di compilazione e output atteso (DecLLM: dal 37% con un tentativo al 74% con 15, Tabella 2) è rinviato. Prima serve una baseline al primo tentativo, anche perché alcuni modelli usati sono più recenti e potenti di quelli dei paper. La ripresa della sessione (§3.2) è già la base tecnica per aggiungerlo.
- **L'offuscamento è rinviato** (LLM4Decompile §5: con Control Flow Flattening e Bogus Control Flow il successo cala di oltre il 70%). Nel container non c'è né O-LLVM né Tigress né `clang`.

---

## 5. Verifiche aggiunte all'analyzer (`ast_analyzer.py`)

### 5.1 Test funzionale (colonne `functional_match`, `functional_pass_rate`)
- **Cosa:** compila e linka originale e decompilato con gli stessi flag (`gcc -O0 -w -lm`), li esegue sugli stessi casi di test e confronta stdout ed exit code.
- **Esecuzione:** il codice generato dall'LLM gira dentro `bwrap`, con filesystem in sola lettura, `/tmp` privato, senza rete e con un timeout di 5 s.
- **Casi di test:** vengono da `originals/<nome>.tests.json` nel formato `[{"args": [...], "stdin": "..."}]`. Senza quel file c'è un solo caso, senza argomenti.
- **Perché:** è la vera "re-executability" dei paper. LLM4Decompile considera riuscito un caso se supera le asserzioni; DecLLM (Definizione 1) se supera tutti i test.
- **Cosa ha mostrato:** sui vecchi run di Gemma il test passava solo in 7 file su 20, e in nessuno dei 5 di Qwythos, nonostante similarità AST spesso intorno all'80%. Esempio: tea_cipher O3 di Gemma calcola il testo cifrato sbagliato.
- **Da sapere:** il confronto dello stdout è esatto, quindi `Original:` invece di `Originale:` fa fallire il test. È coerente con il prompt, che chiede di conservare le stringhe di formato.

### 5.2 AddressSanitizer (colonne `asan_orig`, `asan_dec`, `asan_match`)
- **Cosa:** compila entrambi con `-fsanitize=address` (con `detect_leaks=0`) e registra, per ogni caso di test, il tipo di errore di memoria. `asan_match` vale 1 se coincidono caso per caso.
- **Perché:** DecLLM (§4.4) usa ASan per trovare difetti che il confronto dell'output non vede. Serve anche per i programmi con comportamento indefinito come cwe119: invece di confrontare un segfault casuale, si confronta "stack-buffer-overflow sì o no".
- **Cosa ha mostrato:** `gpt4_1/secure_db_O2_llm.c` supera 5 test su 5, ma con gli input lunghi ha un `heap-buffer-overflow` perché la dimensione della struttura è ricostruita male. È l'errore che DecLLM chiama *ill-inferred buffer size* (§6.3).
- **Requisito:** `libasan`, installata nel container Toolbx con `sudo dnf install libasan`. Senza la libreria le colonne restano vuote.

### 5.3 Classificazione degli errori di compilazione (colonne `compile_error_type`, `compile_error_count`)
- **Categorie:** `link`, `signature`, `declaration`, `struct`, `type`, `syntax`, `other`. Si rifanno a DecLLM §3 (*specification*, *inference* e *template errors*) e a LLM4Decompile Fig. 8.
- **Perché:** sapere *come* falliscono i modelli, e non solo *se* falliscono, permette di confrontare le distribuzioni con quelle dei paper.
- **Verifica:** sui file archiviati la categoria più frequente è `declaration`, per esempio `unknown type name 'uint'`.

### 5.4 Dimensione (colonne `loc_orig`, `loc_dec`, `funcs_orig`, `funcs_dec`)
- **Cosa:** righe di codice senza commenti e numero di funzioni definite.
- **Perché:** entrambi i paper mostrano che le prestazioni calano con la lunghezza del codice. Il numero di funzioni rileva anche file vuoti o ridotti a stub: per esempio `Qwythos-9b/tea_cipher_O3_llm.c` ha 0 righe e 0 funzioni, compila ma non ha il `main`.

### 5.5 Flag di compilazione allineati
- **Cosa:** il controllo di compilazione (`re_executability`) non usa più `-std=c99`, quindi usa gli stessi flag del test funzionale.
- **Perché:** prima un file poteva risultare "non compila" e superare comunque il test funzionale.

---

## 6. Nuovi programmi di test (`originals/`)

### 6.1 Varianti per il test di contaminazione
`tea_cipher_mod.c`, `crc32_mod.c` e `feistel_mod.c` hanno la stessa struttura degli originali ma costanti, numero di round e shift non standard.

**Perché.** TEA, CRC32 e la costante aurea sono molto presenti nei dati di addestramento: un modello può "riconoscere" l'algoritmo e riscriverlo a memoria invece di decompilarlo. Sulle varianti lo si vede subito, perché la versione da manuale produce un output diverso. DecLLM affronta lo stesso problema scegliendo dati successivi al cutoff dei modelli.

### 6.2 Programmi vulnerabili
**Principio di base:** una ricostruzione deve essere fedele anche nei bug. Se la ricostruzione corregge una vulnerabilità, chi analizza il binario non la vede. DecLLM (§7, "Validity in CodeQL Results") riconosce questo rischio come un limite; qui diventa un criterio di valutazione esplicito, cioè la **conservazione delle vulnerabilità**.

| Programma | CWE | Bug | Rilevato da |
|---|---|---|---|
| `cwe119.c` | 119 | `strcpy` in un buffer sullo stack | ASan (stack-buffer-overflow) |
| `cwe134.c` | 134 | `printf(msg)` | test funzionale: `"100%% sicuro"` stampa `100% sicuro` solo se il bug è rimasto; ASan non vede nulla |
| `cwe190.c` | 190 → 122 | dimensione troncata a `uint8_t`, poi heap overflow | ASan con `65` elementi |
| `cwe193.c` | 193 | controllo `>` invece di `>=` | ASan con un nome di 16 caratteri; l'output è identico, il bug si vede solo con ASan |
| `cwe416.c` | 416 | use-after-free della sessione | ASan; con `mario logout 1` la memoria liberata viene riusata e si ottiene l'accesso amministratore |

**Come sono costruiti.**
- Ogni programma ha un `.tests.json` con casi innocui e casi che attivano il bug: un bug che i test non attivano, ASan non lo vede.
- L'output senza ASan è deterministico: gli overflow restano nello spazio che `malloc` arrotonda comunque e lo stdout è senza buffer. Così una ricostruzione fedele non fallisce il test per caso. Verificato su 5 esecuzioni.

**Verifica.** Ho confrontato una ricostruzione "fedele" (l'originale) con una "corretta" (bug sistemato):

| | Fedele | Corretta |
|---|---|---|
| cwe134 | 4/4, ASan ✔ | 2/4 |
| cwe190 | 4/4, ASan ✔ | 3/4, ASan ✘ |
| cwe193 | 5/5, ASan ✔ | 3/5, ASan ✘ |
| cwe416 | 4/4, ASan ✔ | 2/4, ASan ✘ |

`asan_match` è volutamente severo. In `gemma…/cwe119_O3_llm` l'overflow c'è ancora ma è passato da stack a variabile globale, e viene contato come diverso: lo scenario di sfruttamento cambia, perché uno stack overflow può sovrascrivere l'indirizzo di ritorno e un overflow su una variabile globale no.

---

## 7. Come usarlo

```bash
cd "…/Experiments/Python AST controller"

# un programma (O0–O3)
python auto_pipeline.py --source originals/tea_cipher.c --model Qwythos-9b --out Test_v2.csv

# tutti i programmi
for src in originals/*.c; do
  python auto_pipeline.py --source "$src" --model Qwythos-9b --out Test_v2.csv
done 2>&1 | tee run_$(date +%Y%m%d_%H%M).log

# secondo run di conferma: aggiungere --run 2

# ricalcolare il CSV senza rifare le decompilazioni
python run_benchmark.py --root . --out Test_v2.csv
```

- `--model` deve corrispondere al modello configurato in Goose, perché il `CONFIG` dice ancora `gpt4_1`.
- 18 programmi × 4 livelli fanno 72 sessioni, ciascuna fino a 1300 s più i solleciti. Conviene lanciare in `tmux`.
- **Calc:** separatore virgola e lingua "Inglese (USA)" in importazione; aggiornare con *File → Ricarica*; **non salvare sopra il `.csv`**. Se lo si salva, il benchmark considera già calcolate quelle righe e le salta.
- **`--force`:** usarlo solo con un `--out` nuovo. Le righe dei modelli spostati in `Archivio*` sparirebbero, perché quelle cartelle non vengono più lette.
- Se nel log compare `⚠ N accessi fuori sandbox`, quel run va controllato.

### Colonne del CSV

| Colonna | Significato |
|---|---|
| `re_executability` | **Solo compilazione** (`gcc -c`). Nella tesi conviene chiamarla "compilabilità" |
| `functional_match`, `functional_pass_rate` | Supera tutti i test / % di test superati. È la *re-executability* dei paper |
| `compile_error_type`, `compile_error_count` | Categoria più frequente e numero di errori gcc/ld |
| `asan_orig`, `asan_dec`, `asan_match` | Errori di memoria (es. `stack-buffer-overflow`, `none`); `asan_match` = 1 se coincidono caso per caso |
| `loc_*`, `funcs_*` | Righe di codice e numero di funzioni |
| `edit_similarity` | Similarità testuale (`SequenceMatcher`, vedi §8) |
| `ast_node_similarity`, `tree_edit_distance`, `fanout_similarity`, `ast_depth_*`, `*_delta` | Metriche strutturali AST |
| `parse_error` | 1 se pycparser non riesce a fare il parse |
| `sandbox_violations` | Numero di accessi fuori sandbox; vuoto se il run non ha `.meta.json` |

---

## 8. Limiti noti e lavori futuri

**Da sistemare nelle metriche.**
- Il TED e l'istogramma AST ignorano operatori e costanti (§2.3). Andrebbero incluse nelle etichette, per esempio `BinaryOp:+` e `Constant:0x…`.
- `edit_similarity` usa `SequenceMatcher`, non la distanza di Levenshtein del paper: va sostituita oppure dichiarata nella tesi. Il calcolo include anche i commenti; si potrebbe normalizzare rigenerando il codice con `pycparser`.
- La fan-out similarity distingue poco: va tolta dalla media o eliminata.
- Il TED confronta tutto il file, typedef di Ghidra compresi: si potrebbero accoppiare solo le funzioni.

**Rigore sperimentale.**
- Servono 3–5 run per configurazione, riportando media ± deviazione standard oppure pass@k (DecLLM: successo se almeno un run passa su 3).
- La temperatura non viene ancora registrata. LLM4Decompile usa decodifica greedy.

**Esperimenti futuri, in ordine di valore.**
1. **Ciclo di feedback** come in DecLLM: errori di gcc e output atteso passati al modello riprendendo la sessione. Si misura il successo in funzione del numero di iterazioni.
2. **Baseline:** Ghidra da solo (circa 20% in LLM4Decompile, Tab. 3) e Ghidra + LLM in un solo colpo con il prompt di DecGPT (*"Generate linux compilable C/C++ code of the main and other functions in the supplied snippet without using goto, fix any missing headers. Do not explain anything."*). Servono per dimostrare il valore dell'approccio agentico.
3. **Un sottoinsieme di HumanEval-Decompile** (repo GitHub di LLM4Decompile) per confrontarsi direttamente con i numeri pubblicati.
4. **Offuscamento** con O-LLVM o Tigress.
5. **UBSan** per l'integer overflow con segno, attivabile installando `libubsan`.

**Robustezza degli script.**
- Attesa fissa per l'avvio di Ghidra: meglio controllare a intervalli se la porta 8080 risponde.
- Deduplica contorta in `run_benchmark.py`: andrebbe semplificata usando sempre la chiave `(funzione, modello, livello, variante)`.
- `current_model` va sempre passato con `--model`.

---

## 9. Backup

- **CSV vecchi:** sono al sicuro in `Archivio2/` (`results.csv`, `ResultNewPrompt.csv`).
- **Versioni precedenti degli script:** erano state copiate nella cartella temporanea della sessione di Claude Code, che è stata svuotata e **non esiste più**. Le versioni originali di `ast_analyzer.py`, `auto_pipeline.py` e `run_benchmark.py` non sono quindi più recuperabili.
- La cartella del progetto non è sotto git. Per tenere traccia delle modifiche future conviene inizializzarlo (`git init`) e fare un commit dello stato attuale.
