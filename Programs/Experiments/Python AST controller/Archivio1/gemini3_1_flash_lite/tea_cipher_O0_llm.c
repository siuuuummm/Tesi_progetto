#include <stdio.h>
#include <stdint.h>

// TEA Encryption Function
void encrypt(uint32_t *v, const uint32_t *k) {
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = 0;
    uint32_t delta = 0x61c88647;
    
    for (int i = 0; i < 32; i++) {
        sum += delta;
        v0 += ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
        v1 += ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
    }
    
    v[0] = v0;
    v[1] = v1;
}

// TEA Decryption Function
void decrypt(uint32_t *v, const uint32_t *k) {
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = 0xC6EF3720; // 32 * delta
    uint32_t delta = 0x61c88647;
    
    for (int i = 0; i < 32; i++) {
        v1 -= ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
        v0 -= ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
        sum -= delta;
    }
    
    v[0] = v0;
    v[1] = v1;
}

int main() {
    uint32_t data[2] = {0x12345678, 0x9abcdef0};
    uint32_t key[4] = {0xa56babcd, 0, 0xffffffff, 0xabcd1234};
    
    printf("Originale: %08X %08X\n", data[0], data[1]);
    
    encrypt(data, key);
    printf("Cifrato:   %08X %08X\n", data[0], data[1]);
    
    decrypt(data, key);
    printf("Decifrato: %08X %08X\n", data[0], data[1]);
    
    return 0;
}
