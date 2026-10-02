#include <stdio.h>
#include <stdint.h>

void tea_encrypt(uint32_t *v, int *k) {
    int i;
    int sum = 0;
    uint32_t v0 = v[0], v1 = v[1];
    for (i = 0; i < 32; i++) {
        sum -= 0x61c88647;
        v0 += (k[1] + (v1 >> 5)) ^ (v1 * 0x10 + k[0]) ^ (sum + v1);
        v1 += (k[3] + (v0 >> 5)) ^ (v0 * 0x10 + k[2]) ^ (sum + v0);
    }
    v[0] = v0;
    v[1] = v1;
}

void tea_decrypt(uint32_t *v, int *k) {
    int i;
    int sum = -0x3910c8e0;
    uint32_t v0 = v[0], v1 = v[1];
    for (i = 0; i < 32; i++) {
        v1 -= (k[3] + (v0 >> 5)) ^ (v0 * 0x10 + k[2]) ^ (sum + v0);
        v0 -= (k[1] + (v1 >> 5)) ^ (v1 * 0x10 + k[0]) ^ (sum + v1);
        sum += 0x61c88647;
    }
    v[0] = v0;
    v[1] = v1;
}

int main() {
    uint32_t v[2] = {0x12345678, 0x9abcdef0};
    int k[4] = {0xa56babcd, 0, -1, 0xabcd1234};
    
    printf("Originale: %08X %08X\n", v[0], v[1]);
    tea_encrypt(v, k);
    printf("Cifrato:   %08X %08X\n", v[0], v[1]);
    tea_decrypt(v, k);
    printf("Decifrato: %08X %08X\n", v[0], v[1]);
    return 0;
}
