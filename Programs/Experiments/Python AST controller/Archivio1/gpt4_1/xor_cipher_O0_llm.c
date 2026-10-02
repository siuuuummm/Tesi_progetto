#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Ruota a sinistra un intero a 32 bit di 'n' posizioni
uint32_t rol32(uint32_t value, uint8_t n) {
    return (value << (n & 0x1F)) | (value >> (32 - (n & 0x1F)));
}

// Calcola un checksum "debole" XOR con rotazione sui byte
int xor_checksum(const uint8_t *data, int len) {
    uint32_t checksum = 0;
    for(int i = 0; i < len; i++) {
        checksum = rol32(checksum + data[i], 3);
    }
    return checksum;
}

// Applica XOR byte in place con chiave su tutta la stringa
void xor_cipher(uint8_t *data, int len, uint8_t key) {
    for(int i = 0; i < len; i++) {
        data[i] ^= key;
    }
}

int main() {
    char message[17] = "secret message"; // 16+1 char
    size_t len = strlen(message);
    uint8_t key = 0x5A;
    message[len] = key;
    uint32_t orig = xor_checksum((uint8_t*)message, len);
    printf("Checksum originale: %u\n", (unsigned long)orig);

    xor_cipher((uint8_t*)message, len, key);
    uint32_t enc = xor_checksum((uint8_t*)message, (int)len);
    printf("Checksum cifrato:   %u\n", (unsigned long)enc);

    xor_cipher((uint8_t*)message, len, key); // Decifra
    printf("Decifrato: %s\n", message);
    return 0;
}
