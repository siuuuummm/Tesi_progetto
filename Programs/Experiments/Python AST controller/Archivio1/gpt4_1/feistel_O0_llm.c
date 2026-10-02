#include <stdio.h>
#include <stdint.h>

// Prototipi delle funzioni
unsigned int hash_mix(unsigned int key, int round);
void cipher_round(unsigned int *left, unsigned int *right, int k);

// Funzione di hash/mix (ex FUN_00400466)
unsigned int hash_mix(unsigned int key, int round) {
    return (unsigned int)(round + 0x9e3779b9U) ^ ((key << 5) | (key >> 27));
}

// Round di cifratura (ex FUN_00400484)
void cipher_round(unsigned int *left, unsigned int *right, int k) {
    for (unsigned int round = 0; round < 8; ++round) {
        unsigned int l = *left;
        unsigned int r = *right;
        unsigned int mixed = hash_mix(*left, k + round);
        *left = r ^ mixed;
        *right = l;
    }
}

// Funzione principale (ex FUN_004004ec) → main
int main(void) {
    unsigned int left = 0xdeadbeef;
    unsigned int right = 0xcafebabe;
    int key = 0x12345678;
    printf("Originale: %08X %08X\n", left, right);
    cipher_round(&left, &right, key);
    printf("Cifrato:   %08X %08X\n", left, right);
    return 0;
}
