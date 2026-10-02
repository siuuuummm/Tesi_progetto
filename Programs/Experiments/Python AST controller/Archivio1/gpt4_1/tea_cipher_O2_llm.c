#include <stdio.h>
#include <stdint.h>

// TEA encryption (Tiny Encryption Algorithm)
void tea_encrypt(uint32_t *v, uint32_t *key) {
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = 0;
    uint32_t delta = 0x9e3779b9;
    for (int i = 0; i < 32; i++) {
        sum -= delta;
        v0 += ((v1 << 4) + key[0]) ^ (v1 >> 5) + key[1] ^ (sum + v1);
        v1 += ((v0 << 4) + key[2]) ^ (v0 >> 5) + key[3] ^ (sum + v0);
    }
    v[0] = v0;
    v[1] = v1;
}

// TEA decryption
void tea_decrypt(uint32_t *v, uint32_t *key) {
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = 0xC6EF3720; // delta * 32
    uint32_t delta = 0x9e3779b9;
    for (int i = 0; i < 32; i++) {
        v1 -= ((v0 << 4) + key[2]) ^ (v0 >> 5) + key[3] ^ (v0 + sum);
        v0 -= ((v1 << 4) + key[0]) ^ (v1 >> 5) + key[1] ^ (v1 + sum);
        sum += delta;
    }
    v[0] = v0;
    v[1] = v1;
}

int main() {
    uint32_t key[4] = {0};
    // Le costanti usate nel disassemblato: indirizzi pseudo _DAT_004011e0 ecc
    // ma useremo chiave fittizia di zero.

    uint32_t data[2] = {0x12345678, 0x9abcdef0};

    printf("Originale: %08X %08X\n", data[0], data[1]);
    tea_encrypt(data, key);
    printf("Cifrato:   %08X %08X\n", data[0], data[1]);
    tea_decrypt(data, key);
    printf("Decifrato: %08X %08X\n", data[0], data[1]);
    return 0;
}
