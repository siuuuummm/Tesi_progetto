# Batteria di test per benchmark di decompilazione

10 programmi C autonomi, compilabili con `gcc -O0..3 file.c -lm`, ognuno con
un `main` che esercita le funzioni (utile per verificare la re-executability).
Tutti verificati: 40/40 compilazioni pulite, output funzionale corretto.

## Programmi per difficolta crescente

| Programma        | Categoria        | Difficolta   | Cosa stressa nelle metriche |
|------------------|------------------|--------------|------------------------------|
| bubble_sort.c    | Algoritmi        | Facile       | Loop annidati, profondita AST bassa |
| xor_cipher.c     | Crypto           | Media        | Operazioni bitwise, shift, rotazioni |
| quicksort.c      | Algoritmi        | Media        | Ricorsione, partizione, swap |
| search_math.c    | Algoritmi        | Media        | Ricerca binaria + chiamate libm (sqrt, pow) |
| linked_list.c    | Strutture dati   | Media        | struct + puntatori, malloc/free |
| string_ops.c     | Algoritmi        | Media-alta   | Aritmetica puntatori su char, indicizzazione |
| crc32.c          | Crypto           | Alta         | Tabella lookup, bitwise intensivo |
| hash_table.c     | Strutture dati   | Alta         | Array di puntatori a struct, hashing |
| bst.c            | Strutture dati   | Alta         | Ricorsione + struct annidate (left/right) |
| tea_cipher.c     | Crypto           | Molto alta   | Cifrario a blocchi, costanti magiche, overflow uint32 |

## Perche questa selezione

La difficolta cresce lungo gli assi che le tue metriche misurano:

- **Profondita AST e control flow**: da `bubble_sort` (2 loop) a `bst` (ricorsione su albero).
- **Recupero tipi user-defined**: le strutture dati (`struct Node`, `struct TreeNode`,
  `struct Entry`) vengono perse in compilazione — e' esattamente il punto debole
  evidenziato nel paper LLM4Decompile per ExeBench.
- **Operazioni a basso livello**: i programmi crypto usano shift, xor, rotazioni e
  overflow-wrapping, che i decompilatori traducono in modi molto diversi tra O0 e O3.
- **Chiamate esterne**: `search_math` usa libm, `linked_list`/`hash_table` usano
  malloc — verifica se il decompilatore riconosce le funzioni di libreria.

I programmi crypto (`tea_cipher`, `crc32`, `xor_cipher`) sono in linea con i tuoi
`feistel` e `secure_db`, cosi mantieni coerenza tematica nella tesi.

## Uso con la tua pipeline

```bash
# Singolo programma, tutti i livelli
python auto_pipeline.py --source test_programs/crypto_security/tea_cipher.c

# In loop su tutta la batteria
for f in test_programs/*/*.c; do
    python auto_pipeline.py --source "$f"
done
```

## Aspettative sui risultati

In base al paper, dovresti osservare:
- **O0** quasi sempre rieseguibile e con AST simile (poca ottimizzazione).
- **O2/O3** calo netto: inlining, loop unrolling e tail-call rendono il binario
  molto diverso dal sorgente. `tea_cipher` e `bst` a O3 sono i candidati piu
  probabili al fallimento.
- **Strutture dati**: edit similarity bassa per la perdita dei nomi di campo,
  ma TED e fan-out possono restare alti se la struttura logica e' preservata.
