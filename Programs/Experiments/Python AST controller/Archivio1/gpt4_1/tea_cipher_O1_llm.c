#include <stdio.h>
#include <stdint.h>

// Funzione di cifratura, implementazione simile al TEA (Tiny Encryption Algorithm)
void tea_encrypt(uint32_t *v, int *k) {
    uint32_t v0 = v[0], v1 = v[1];
    int sum = 0;
    do {
        sum -= 0x61C88647;
        v0 += (((v1 << 4) + k[0]) ^ ((v1 >> 5) + k[1]) ^ (sum + v1));
        v1 += (((v0 << 4) + k[2]) ^ ((v0 >> 5) + k[3]) ^ (sum + v0));
    } while (sum != -0x3910c8e0);
    v[0] = v0;
    v[1] = v1;
}

// Funzione di decifratura
void tea_decrypt(uint32_t *v, int *k) {
    uint32_t v0 = v[0], v1 = v[1];
    int sum = -0x3910c8e0;
    do {
        v1 -= (((v0 << 4) + k[2]) ^ ((v0 >> 5) + k[3]) ^ (v0 + sum));
        v0 -= (((v1 << 4) + k[0]) ^ ((v1 >> 5) + k[1]) ^ (v1 + sum));
        sum += 0x61C88647;
    } while (sum != 0);
    v[0] = v0;
    v[1] = v1;
}

int main() {
    int key[4] = {0xA56BABCD, 0, -1, 0xABCD1234};
    uint32_t data[2] = {0x12345678, 0x9ABCDEF0};
    printf("Originale: %08X %08X\n", data[0], data[1]);

    tea_encrypt(data, key);
    printf("Cifrato:   %08X %08X\n", data[0], data[1]);

    tea_decrypt(data, key);
    printf("Decifrato: %08X %08X\n", data[0], data[1]);
    return 0;
}
