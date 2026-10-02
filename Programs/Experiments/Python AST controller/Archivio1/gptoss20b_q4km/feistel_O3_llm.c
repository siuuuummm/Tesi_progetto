#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Simple Feistel round function (example)
uint32_t feistel_round(uint32_t half, uint32_t key) {
    // Example: rotate left by 5 and XOR with key
    return ((half << 5) | (half >> (32 - 5))) ^ key;
}

// Feistel cipher encrypt/decrypt for 64-bit block using two rounds
uint64_t feistel_encrypt(uint64_t plaintext, uint32_t k1, uint32_t k2) {
    uint32_t L = (uint32_t)(plaintext >> 32);
    uint32_t R = (uint32_t)(plaintext & 0xFFFFFFFFU);
    // Round 1
    uint32_t newR = feistel_round(R, k1) ^ L;
    uint32_t newL = R;
    // Round 2
    uint32_t finalR = feistel_round(newR, k2) ^ newL;
    uint32_t finalL = newR;
    return ((uint64_t)finalL << 32) | (uint64_t)finalR;
}

uint64_t feistel_decrypt(uint64_t ciphertext, uint32_t k1, uint32_t k2) {
    // Decryption uses keys in reverse order
    uint32_t L = (uint32_t)(ciphertext >> 32);
    uint32_t R = (uint32_t)(ciphertext & 0xFFFFFFFFU);
    // Round 1 (key2)
    uint32_t newR = feistel_round(R, k2) ^ L;
    uint32_t newL = R;
    // Round 2 (key1)
    uint32_t finalR = feistel_round(newR, k1) ^ newL;
    uint32_t finalL = newR;
    return ((uint64_t)finalL << 32) | (uint64_t)finalR;
}

int main() {
    const char *msg = "Hello!"; // 6 bytes, pad to 8
    uint64_t block = 0;
    memcpy(&block, msg, strlen(msg));
    uint32_t k1 = 0xA5A5A5A5U;
    uint32_t k2 = 0x5A5A5A5AU;
    uint64_t enc = feistel_encrypt(block, k1, k2);
    printf("Encrypted: %016llX\n", (unsigned long long)enc);
    uint64_t dec = feistel_decrypt(enc, k1, k2);
    char out[9] = {0};
    memcpy(out, &dec, 8);
    printf("Decrypted: %s\n", out);
    return 0;
}
