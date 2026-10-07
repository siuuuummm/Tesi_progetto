/* tea_cipher.c — Difficolta: MOLTO ALTA
 * Tiny Encryption Algorithm (TEA). Cifrario a blocchi con costanti magiche,
 * shift, somme overflow-wrapping su uint32. Simile per natura al tuo feistel:
 * uno dei casi piu ostici per la decompilazione a O2/O3. */
#include <stdio.h>
#include <stdint.h>

void tea_encrypt(uint32_t v[2], const uint32_t key[4]) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0;
    const uint32_t delta = 0x9E3779B9u;
    for (int i = 0; i < 32; i++) {
        sum += delta;
        v0 += ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + key[1]);
        v1 += ((v0 << 4) + key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + key[3]);
    }
    v[0] = v0;
    v[1] = v1;
}

void tea_decrypt(uint32_t v[2], const uint32_t key[4]) {
    uint32_t v0 = v[0], v1 = v[1];
    const uint32_t delta = 0x9E3779B9u;
    uint32_t sum = delta * 32;
    for (int i = 0; i < 32; i++) {
        v1 -= ((v0 << 4) + key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + key[3]);
        v0 -= ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + key[1]);
        sum -= delta;
    }
    v[0] = v0;
    v[1] = v1;
}

int main(void) {
    uint32_t data[2] = {0x12345678u, 0x9ABCDEF0u};
    uint32_t key[4]  = {0xA56BABCDu, 0x00000000u, 0xFFFFFFFFu, 0xABCD1234u};

    printf("Originale: %08X %08X\n", data[0], data[1]);

    tea_encrypt(data, key);
    printf("Cifrato:   %08X %08X\n", data[0], data[1]);

    tea_decrypt(data, key);
    printf("Decifrato: %08X %08X\n", data[0], data[1]);

    return 0;
}
