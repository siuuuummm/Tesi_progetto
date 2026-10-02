#include <stdio.h>
#include <stdint.h>

// Funzioni do-nothing (potenzialmente usate per INIT/FINI)
void do_nothing_1(void) {}
void do_nothing_2(void) {}
void do_nothing_3(void) {}

// Funzione di round elementare per cifratura
uint32_t calc_cipher_round(uint32_t val, int key) {
    return ((val << 5) | (val >> 27)) ^ (key + 0x9e3779b9U);
}

// Blocco completo di cifratura: cifra due parole tramite round multipli
void cipher_block(uint32_t *val1, uint32_t *val2, int round_start) {
    uint32_t key = round_start + 0x9e3779b9U;
    uint32_t prev = *val2;
    do {
        uint32_t old = *val1;
        uint32_t result = ((old << 5) | (old >> 27)) ^ key;
        key++;
        *val1 = result ^ prev;
        *val2 = old;
        prev = old;
    } while (key != (uint32_t)(round_start + 0x9e3779c1U));
}

// Funzione che chiama un puntatore esterno (non usata nel main ricostruito)
void call_external(void) {
    // Placeholder: funzione esterna via puntatore
    // In decompilato: (*(code *)PTR_00402ff8)();
}

// Funzione principale individuata (main)
int main(void) {
    printf("Originale: %08X %08X\n", 0xdeadbeef, 0xcafebabe);
    uint32_t round_var = 0xb06bd031;
    uint32_t val2 = 0xcafebabe;
    uint32_t val1 = 0xdeadbeef;
    uint32_t result = 0;
    while (round_var != 0xb06bd039) {
        uint32_t temp = ((val1 << 5) | (val1 >> 27)) ^ round_var;
        round_var++;
        result = temp ^ val2;
        val2 = val1;
        val1 = result;
    }
    printf("Cifrato:   %08X %08X\n", result, val2);
    return 0;
}

// _INIT e _DT_FINI wrapper
void _INIT_0(void) { do_nothing_3(); }
void _DT_FINI(void) { return; }

// Entry point wrapper (NON utilizzato in main C standard)
void entry(void *param_1, void *param_2) {
    // (*(code *)PTR___libc_start_main_00402fd8)(main, param_2, &stack0x00000008, 0, 0, param_1, auStack_8);
    // while (1) ;
}
