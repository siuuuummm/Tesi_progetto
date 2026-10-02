#include <stdio.h>
#include <string.h>
#include <stdint.h>

// --- Funzione: Rotazione circolare a sinistra su 32 bit ---
uint32_t rol32(uint32_t value, uint8_t shift) {
    return (value << (shift & 0x1f)) | (value >> (32 - (shift & 0x1f)));
}

// --- Funzione: Checksum custom su buffer ---
int custom_checksum(const char *buf, int len) {
    uint32_t acc = 0;
    for (int i = 0; i < len; i++) {
        acc = rol32(acc + (uint8_t)buf[i], 3);
    }
    return acc;
}

// --- Funzione: XOR in-place su buffer con chiave (byte) ---
void xor_cipher(char *buf, int len, uint8_t key) {
    for (int i = 0; i < len; i++) {
        buf[i] ^= key;
    }
}

int main() {
    char text[16];
    strcpy(text, "secret message");
    size_t len = strlen(text);
    uint8_t key = 0x5a;

    uint32_t orig = custom_checksum(text, len);
    printf("Checksum originale: %u\n", orig);

    xor_cipher(text, len, key);
    uint32_t enc = custom_checksum(text, len);
    printf("Checksum cifrato:   %u\n", enc);

    xor_cipher(text, len, key);
    printf("Decifrato: %s\n", text);
    return 0;
}
