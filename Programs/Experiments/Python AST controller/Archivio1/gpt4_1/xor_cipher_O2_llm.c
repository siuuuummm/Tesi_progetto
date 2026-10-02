#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Util functions (reverse engineered names)

// Performs a rolling checksum (used by main)
uint rolling_checksum(uint8_t *data, int n) {
    uint32_t result = 0;
    if (n > 0) {
        uint8_t *end = data + n;
        while (data != end) {
            result = ((result + *data) * 8) | ((result + *data) >> 29);
            data++;
        }
    }
    return result;
}

// Performs xor on buffer with a single char key (used by main)
void xor_cipher32(uint32_t *buf, uint32_t len, uint8_t key) {
    if (len <= 0) return;

    uint32_t pattern = 0;
    if (len - 1 >= 0xf)
        pattern = ((uint32_t)key << 24) | ((uint32_t)key << 16) | ((uint32_t)key << 8) | key;

    uint32_t blocks = len / 16;
    for (uint32_t *p = buf, *end = buf + blocks * 4; p != end; p += 4) {
        p[0] ^= pattern;
        p[1] ^= pattern;
        p[2] ^= pattern;
        p[3] ^= pattern;
    }

    uint32_t i = blocks * 16;
    uint8_t *b = (uint8_t *)buf;
    for (; i < len; ++i) {
        b[i] ^= key;
    }
}

// Rotate left by n bits
uint32_t rol(uint32_t val, uint8_t sh) {
    return (val << (sh & 0x1f)) | (val >> (32 - (sh & 0x1f)));
}

// program entry
int main() {
    // TODO: Check what DAT_004011c8 is supposed to be (its content is missing!)
    // We'll use a placeholder value
    uint64_t DAT_004011c8 = 0x1122334455667788ULL;

    // Pre-set buffer to analyze
    union {
        uint64_t u64;
        uint8_t bytes[16];
    } secret = { .u64 = 0x207465726365736dULL };
    // msessage
    uint8_t message[16] = {0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x00};

    // First checksum (original)
    uint32_t sum = rolling_checksum((uint8_t *)&secret, 7);
    printf("Checksum originale: %u\n", sum);
    
    // XOR and checksum (ciphered)
    secret.u64 ^= DAT_004011c8;
    for (int i=8; i<14; ++i) {
        ((uint8_t*)&secret)[i] ^= 0x5a;
    }
    sum = rolling_checksum((uint8_t *)&secret, 7);
    printf("Checksum cifrato:   %u\n", sum);

    // Apply xor again to decode and output
    secret.u64 ^= DAT_004011c8;
    for (int i=8; i<14; ++i) {
        ((uint8_t*)&secret)[i] ^= 0x5a;
    }
    printf("Decifrato: %s\n", (char *)&secret);
    return 0;
}
