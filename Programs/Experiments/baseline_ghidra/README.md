# Baseline con il solo Ghidra

Termine di confronto per le ricostruzioni dei modelli (sezioni 4.5 e 6.2 della tesi).
Per ciascuno dei 20 binari (5 programmi × O0–O3) si esporta il codice che Ghidra
produce per il `main` e per le funzioni raggiungibili da esso, e lo si rende
compilabile **solo con aggiunte**: definizioni dei tipi di Ghidra (`undefined4` e
simili), header standard, prototipi delle funzioni e nome `main`. I corpi delle
funzioni restano identici, come nella baseline di Liu, Raff e Micinski
(arXiv:2609.05370). Il risultato passa nella stessa valutazione delle
ricostruzioni dei modelli.

| File | Contenuto |
|---|---|
| `ExportBaseline.py` | script Jython per Ghidra headless: trova il `main` e lo esporta con le funzioni raggiungibili |
| `assembla.py` | aggiunge tipi, header, prototipi e rinomina il `main` |
| `run_baseline.sh` | esegue tutto e aggiorna `risultati.csv` e `decompilato/` |
| `decompilato/` | i 20 file valutati |
| `risultati.csv` | valutazione, nello stesso formato di `risultati_finali.csv` |

Risultato: 10 file su 20 compilano, e tutti e 10 conservano la vulnerabilità.
Ghidra è deterministico, quindi basta un'esecuzione per binario. Requisiti come
nel README principale; per rieseguire: `sh run_baseline.sh`.
