#include <stdio.h>
#include <stdint.h>

/**
 * Stampa lo stato originale, applica una semplice cifratura, poi stampa il risultato.
 */
int main(void) {
    uint32_t value1 = 0xdeadbeef;
    uint32_t value2 = 0xcafebabe;
    printf("Originale: %08X %08X\n", value1, value2);
    encrypt_algorithm(&value1, &value2, 0x12345678);
    printf("Cifrato:   %08X %08X\n", value1, value2);
    return 0;
}

/**
 * Algoritmo di cifratura custom.
 * Ruota value1, xor con value2, aggiunge costante iniziale, ripete per alcuni round.
 * @param value1_ptr Pointer al primo valore da cifrare (verrà sovrascritto)
 * @param value2_ptr Pointer al secondo valore da cifrare (verrà sovrascritto)
 * @param round_start Valore di partenza per il round (seed/chiave)
 */
void encrypt_algorithm(uint32_t *value1_ptr, uint32_t *value2_ptr, int round_start) {
    uint32_t round = (uint32_t)round_start + 0x9e3779b9U;
    while (round != (uint32_t)round_start + 0x9e3779c1U) {
        uint32_t tmp = *value1_ptr;
        // Left rotate di 5, xor con l'altro valore e la costante corrente
        *value1_ptr = ((tmp << 5) | (tmp >> (32-5))) ^ (*value2_ptr) ^ round;
        *value2_ptr = tmp;
        round++;
    }
}

/**
 * Helper: effettua una rotazione e un'operazione xor+add, usata solo internamente.
 */
uint32_t encrypt_round_step(uint32_t value, int param) {
    // Left rotate di 5, xor con il secondo parametro aggiungendo costante
    return ((value << 5) | (value >> (32-5))) ^ (param + 0x9e3779b9U);
}

/* Funzioni placeholder (vuote, non usate) */
void unused_placeholder_1(void) { return; }
void unused_placeholder_2(void) { return; }
void unused_placeholder_3(void) { return; }
void unused_dt_init(void) { return; } // _DT_INIT
void unused_fini(void) { return; }    // _DT_FINI

/*
 * Nota: la funzione entry e il riferimento a __libc_start_main sono solo per il bootstrap
 * (non vanno inclusi in normali programmi C utente)
 */
