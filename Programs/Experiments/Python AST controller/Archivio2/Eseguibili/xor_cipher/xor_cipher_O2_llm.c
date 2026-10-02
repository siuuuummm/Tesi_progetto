#include <stdio.h>
#include <stdint.h>
#include <string.h>

// XOR ciphertext key constant (placeholder value, as original is obfuscated)
#define XOR_KEY 0x5a
// Obfuscated checksum XOR constant (placeholder, as DAT_004011c8 is unknown)
#define CHECKSUM_XOR_CONST 0ULL // Sostituire con valore reale se noto

// Funzione di cifratura XOR su buffer di uint32_t/bytes
typedef uint8_t byte;

void xor_cipher(uint32_t *data, uint32_t len, byte key) {
    if (len <= 0) return;
    uint32_t repeat = len / 16;
    uint32_t remaining = len & 0xf;
    uint32_t v = ((uint32_t)key << 24) | ((uint32_t)key << 16) | ((uint32_t)key << 8) | key;
    uint32_t *ptr = data;
    for (uint32_t i = 0; i < repeat; ++i) {
        ptr[0] ^= v;
        ptr[1] ^= v;
        ptr[2] ^= v;
        ptr[3] ^= v;
        ptr += 4;
    }
    byte *bptr = (byte *)data + (repeat * 16);
    for (uint32_t i = 0; i < remaining; ++i) {
        bptr[i] ^= key;
    }
}

uint32_t rol32(uint32_t value, byte n) {
    n &= 0x1f;
    return (value << n) | (value >> (32 - n));
}

uint32_t checksum(const byte *data, int len) {
    if (len <= 0) return 0;
    uint32_t sum = 0;
    for (int i = 0; i < len; ++i) {
        sum += data[i];
        sum = rol32(sum, 3);
    }
    return sum;
}

// Funzione principale ripristinata dal main (FUN_00400380)
int main(void) {
    // Costruzione buffer dati (message + terminatore)
    byte buffer[15] = { /* 0x6d, ... "messagge" + ... */
        /* Restituito dalle costanti in reverse: "secret message" (da funzioni/asm) */
        's', 'e', 'c', 'r', 'e', 't', ' ',
        'm', 'e', 's', 's', 'a', 'g', 'e', 0
    };
    // Calcolo checksum originale
    uint32_t orig_sum = checksum(buffer, 14);
    printf("Checksum originale: %u\n", orig_sum);

    // Cifratura XOR
    *(uint64_t *)buffer = *(uint64_t *)buffer ^ CHECKSUM_XOR_CONST; // Placeholder per operazioni xor simili operate in asm, DAT_004011c8 ignoto
    for (int i = 8; i < 14; ++i)
        buffer[i] ^= XOR_KEY;
    uint32_t ciphered_sum = checksum(buffer, 14);
    printf("Checksum cifrato:   %u\n", ciphered_sum);

    // Decifratura XOR
    *(uint64_t *)buffer = *(uint64_t *)buffer ^ CHECKSUM_XOR_CONST;
    for (int i = 8; i < 14; ++i)
        buffer[i] ^= XOR_KEY;
    printf("Decifrato: %s\n", buffer);
    return 0;
}
