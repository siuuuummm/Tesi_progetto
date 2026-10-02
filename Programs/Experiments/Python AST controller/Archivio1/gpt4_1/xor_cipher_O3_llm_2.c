#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Funzione di utility: rotazione a sinistra
typedef uint32_t u32;
	u32 rol32(u32 value, unsigned int count) {
    return (value << (count & 0x1f)) | (value >> (32 - (count & 0x1f)));
}

// Funzione di checksum rolling
uint32_t rolling_checksum(const uint8_t *data, int len) {
    uint32_t acc = 0;
    for (int i = 0; i < len; ++i) {
        acc = rol32(acc + data[i], 3);
    }
    return acc;
}

// Funzione di cifratura XOR ottimizzata (block e remainder, vect)
void xor_cipher_optimized(uint8_t *buf, uint32_t len, uint8_t key) {
    if (len <= 0) return;
    uint32_t whole_blocks = len / 16;
    uint32_t tail = len % 16;
    uint8_t vect[16];
    for (int j = 0; j < 16; ++j) vect[j] = key;
    // Blocchi da 16 byte
    for (uint32_t i = 0; i < whole_blocks; ++i) {
        for (int j = 0; j < 16; ++j) {
            buf[i * 16 + j] ^= vect[j];
        }
    }
    // Tail finale a byte
    for (uint32_t i = len - tail; i < len; ++i) {
        buf[i] ^= key;
    }
}

int main() {
    // Messaggio cifrato in due QWORD, come nello stack del main
    uint64_t stack1 = 0x6d20746572636573ULL; // 'secret m'
    uint64_t stack2 = 0x6567617373656dULL;   // 'message'
    uint8_t buf[15];
    memcpy(buf, &stack1, 8);
    memcpy(buf + 7, &stack2, 8);
    // Checksum originale
    printf("Checksum originale: %u\n", 0xf779499u);
    // Chiave derivata da costanti statiche (simulato per esempio)
    uint32_t key32 = 0x5a5a; // placeholder (XOR word)
    uint8_t key = key32 & 0xFF;
    xor_cipher_optimized(buf, 15, key);
    uint32_t encrypted_chksum = rolling_checksum(buf, 15);
    printf("Checksum cifrato:   %u\n", encrypted_chksum);
    // Decifra e stampa il messaggio
    xor_cipher_optimized(buf, 15, key);
    printf("Decifrato: %s\n", buf);
    return 0;
}
