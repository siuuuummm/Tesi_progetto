#include <stdio.h>
#include <stdint.h>

// TEA Constants
#define TEA_DELTA 0x9e3779b9
#define TEA_SUM_LIMIT 0xc6ef3720

// Standard TEA Encryption algorithm
void tea_encrypt(uint32_t *v, uint32_t *k) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0;
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
    for (int i = 0; i < 32; i++) {
        sum += TEA_DELTA;
        v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
    }
    v[0] = v0;
    v[1] = v1;
}

// Standard TEA Decryption algorithm
void tea_decrypt(uint32_t *v, uint32_t *k) {
    uint32_t v0 = v[0], v1 = v[1], sum = TEA_SUM_LIMIT;
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
    for (int i = 0; i < 32; i++) {
        v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        sum -= TEA_DELTA;
    }
    v[0] = v0;
    v[1] = v1;
}

int main() {
    // Data to be encrypted/decrypted
    uint32_t data[2] = {0x12345678, 0x9abcdef0};
    
    // The key is loaded from 0x004011e0 in the original binary.
    // Replace with actual 128-bit key if known.
    uint32_t key[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000}; 

    printf("Originale: %08X %08X\n", data[0], data[1]);

    tea_encrypt(data, key);
    printf("Cifrato:   %08X %08X\n", data[0], data[1]);

    tea_decrypt(data, key);
    printf("Decifrato: %08X %08X\n", data[0], data[1]);

    return 0;
}
