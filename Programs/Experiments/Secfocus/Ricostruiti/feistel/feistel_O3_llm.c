#include <stdio.h>
#include <stdint.h>

// Applica una singola operazione di cifratura su due blocchi
uint feistel_round(uint value, int param) {
    return ((value << 5) | (value >> 27)) ^ (param + 0x9e3779b9U);
}

// Applica 8 round (non standard) di feistel modificato
void feistel_encrypt_multi_round(uint32_t *left, uint32_t *right, int param) {
    uint32_t l = *left;
    uint32_t r = *right;
    l = (param + 0x9e3779b9U) ^ r ^ ((l << 5) | (l >> 27));
    r = l;
    l = (param + 0x9e3779baU) ^ r ^ ((l << 5) | (l >> 27));
    r = l;
    l = (param + 0x9e3779bbU) ^ r ^ ((l << 5) | (l >> 27));
    r = l;
    l = (param + 0x9e3779bcU) ^ r ^ ((l << 5) | (l >> 27));
    r = l;
    l = (param + 0x9e3779bdU) ^ r ^ ((l << 5) | (l >> 27));
    r = l;
    l = (param + 0x9e3779beU) ^ r ^ ((l << 5) | (l >> 27));
    r = l;
    l = (param + 0x9e3779bfU) ^ r ^ ((l << 5) | (l >> 27));
    r = l;
    l = (param + 0x9e3779c0U) ^ r ^ ((l << 5) | (l >> 27));
    r = l;
    *left = l;
    *right = r;
}

// Funzione main originale
int main(void) {
    printf("Originale: %08X %08X\n", 0xdeadbeef, 0xcafebabe);
    printf("Cifrato:   %08X %08X\n", 0x9dee733b, 0xc7802f9d);
    return 0;
}
