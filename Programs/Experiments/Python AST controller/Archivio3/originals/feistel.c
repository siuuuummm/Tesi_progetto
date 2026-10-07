#include <stdint.h>
#include <stdio.h>

uint32_t f_function(uint32_t r, uint32_t key) {
    return ((r << 5) | (r >> 27)) ^ (key + 0x9E3779B9);
}

void custom_encrypt(uint32_t *left, uint32_t *right, uint32_t key) {
    for (int i = 0; i < 8; i++) {
        uint32_t temp = *left;
        *left = *right ^ f_function(*left, key + i);
        *right = temp;
    }
}

int main() {
    uint32_t L = 0xDEADBEEF;
    uint32_t R = 0xCAFEBABE;
    uint32_t key = 0x12345678;

    printf("Originale: %08X %08X\n", L, R);
    custom_encrypt(&L, &R, key);
    printf("Cifrato:   %08X %08X\n", L, R);
    
    return 0;
}
