#include <stdio.h>
#include <stdint.h>

// Stampa due valori originali, li cifra, e stampa il risultato
int main(void) {
    uint32_t l = 0xdeadbeef;
    uint32_t r = 0xcafebabe;

    printf("Originale: %08X %08X\n", l, r);

    uint32_t round = 0xb06bd031;
    uint32_t prev_r = r;
    uint32_t prev_l = l;
    uint32_t cipher = 0;

    do {
        uint32_t tmp = ((prev_l << 5) | (prev_l >> 27)) ^ round;
        round += 1;
        cipher = tmp ^ prev_r;
        prev_r = prev_l;
        prev_l = cipher;
    } while (round != 0xb06bd039);

    printf("Cifrato:   %08X %08X\n", cipher, prev_r);
    return 0;
}

// Una funzione di cifra a singolo round, utilizzata altrove (non usata dal main)
uint32_t calc_cipher_round(uint32_t value, int round_key) {
    return ((value << 5) | (value >> 27)) ^ (round_key + 0x9e3779b9U);
}

// Cifra un blocco di due uint32_t usando un ciclo simile a quello del main
void cipher_block(uint32_t *left, uint32_t *right, int round_base) {
    uint32_t round = round_base + 0x9e3779b9U;
    uint32_t prev_r = *right;
    do {
        uint32_t prev_l = *left;
        uint32_t tmp = ((prev_l << 5) | (prev_l >> 27)) ^ round;
        round += 1;
        *left = tmp ^ prev_r;
        *right = prev_l;
        prev_r = prev_l;
    } while (round != round_base + 0x9e3779c1U);
}

// Funzioni di servizio che non fanno nulla
void do_nothing_1(void) { return; }
void do_nothing_2(void) { return; }
void do_nothing_3(void) { return; }

// Queste funzioni sarebbero usate dallo startup del binario. Le lasciamo vuote.
void _DT_INIT(void) { return; }
void _FINI_0(void) { return; }
void _INIT_0(void) { return; }
