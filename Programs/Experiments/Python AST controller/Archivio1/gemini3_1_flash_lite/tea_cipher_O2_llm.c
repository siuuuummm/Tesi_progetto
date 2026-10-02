#include <stdio.h>
#include <stdint.h>

void encrypt(uint32_t *v, uint32_t *k) {
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = 0;
    uint32_t delta = 0x9E3779B9;
    for (int i = 0; i < 32; i++) {
        sum += delta;
        v0 += ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
        v1 += ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
    }
    v[0] = v0;
    v[1] = v1;
}

void decrypt(uint32_t *v, uint32_t *k) {
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t delta = 0x9E3779B9;
    uint32_t sum = delta * 32;
    for (int i = 0; i < 32; i++) {
        v1 -= ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
        v0 -= ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
        sum -= delta;
    }
    v[0] = v0;
    v[1] = v1;
}

int main() {
    uint32_t v[2] = {0x12345678, 0x9abcdef0};
    uint32_t k[4] = {0x004011e0, 0x004011e8, 0x004011f0, 0x004011f4}; // Placeholder based on Ghidra analysis

    printf("Originale: %08X %08X\n", v[0], v[1]);
    
    encrypt(v, k);
    printf("Cifrato:   %08X %08X\n", v[0], v[1]);
    
    decrypt(v, k);
    printf("Decifrato: %08X %08X\n", v[0], v[1]);
    
    return 0;
}
