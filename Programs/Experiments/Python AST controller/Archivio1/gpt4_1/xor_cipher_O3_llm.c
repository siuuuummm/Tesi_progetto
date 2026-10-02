// Ricostruzione del sorgente "xor_cipher_O3_llm.c" reverse engineering
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DATA_PTR ((uint64_t*)0x004011c8)

// --- Funzione utility: rotate left su 32 bit ---
uint32_t rol(uint32_t value, uint8_t amount) {
    return (value << (amount & 0x1f)) | (value >> (32 - (amount & 0x1f)));
}

// --- Funzione: checksum su byte array (ROL-based) ---
uint32_t calc_checksum(uint8_t *data, int len) {
    if (len <= 0) return 0;
    uint32_t acc = 0;
    uint8_t *end = data + len;
    while (data != end) {
        acc += *data++;
        acc = rol(acc, 3);
    }
    return acc;
}

// --- Funzione: cifratura XOR veloce SIMD (ridotta) ---
void xor_cipher(uint8_t *data, uint32_t len, uint8_t key) {
    uint32_t i = 0;
    if ((int)len > 0) {
        // Simulazione C del ciclo vettorizzato/parzialmente disassemblato
        for (; i + 15 < len; i += 16) {
            for (int j = 0; j < 16; ++j)
                data[i + j] ^= key;
        }
        for (; i < len; ++i)
            data[i] ^= key;
    }
}

int main() {
    // Sezione: dati (stringa cifrata) costruiti come in asm
    uint8_t ciphertext[15] = {0x73,0x65,0x63,0x72,0x65,0x74,0x20,0x6d,0x65,0x73,0x73,0x61,0x67,0x65,0};
    uint32_t orig_checksum = 0xf779499u;

    printf("Checksum originale: %u\n", orig_checksum);
    // Simula obfuscazione XOR con costante (campo dati fissa 0x004011c8, ignorabile qui)
    uint8_t key = 0x5a;
    xor_cipher(ciphertext, 14, key); // Cifra stringa
    uint32_t crypt_checksum = calc_checksum(ciphertext, 14);
    printf("Checksum cifrato:   %u\n", crypt_checksum);
    xor_cipher(ciphertext, 14, key); // Decifra stringa
    printf("Decifrato: %s\n", (char*)ciphertext);
    return 0;
}
