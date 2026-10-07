/* feistel_mod.c — variante di feistel.c per il test di contaminazione.
 * Rotazione, costante e numero di round diversi dall'originale (che usa la
 * costante "aurea" 0x9E3779B9, molto presente nei dati di addestramento). */
#include <stdint.h>
#include <stdio.h>

uint32_t f_function(uint32_t r, uint32_t key) {
    return ((r << 11) | (r >> 21)) ^ (key + 0x5F3A1C27);
}

void custom_encrypt(uint32_t *left, uint32_t *right, uint32_t key) {
    for (int i = 0; i < 12; i++) {
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
