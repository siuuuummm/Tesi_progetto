#include <stdio.h>
#include <string.h>
#include <stdint.h>

// CRC32 implementation based on the decompiled logic
// Polynomial: 0xEDB88320 (0x12477ce0 reflected)

uint32_t crc32_table[256];

void init_crc32_table() {
    uint32_t polynomial = 0xEDB88320;
    for (uint32_t i = 0; i < 256; i++) {
        uint32_t crc = i;
        for (uint32_t j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ polynomial;
            } else {
                crc >>= 1;
            }
        }
        crc32_table[i] = crc;
    }
}

uint32_t calculate_crc32(const char *str) {
    uint32_t crc = 0xFFFFFFFF;
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        crc = (crc >> 8) ^ crc32_table[(crc ^ (uint8_t)str[i]) & 0xFF];
    }
    return ~crc;
}

int main() {
    init_crc32_table();
    
    // The decompiled code shows an array of string pointers being processed.
    // Based on the structure, it seems to iterate through a list of strings.
    // For the sake of this reconstructed example, I will include a representative set.
    const char *test_strings[] = {
        "Hello",
        "World",
        "CRC32"
    };
    
    for (int i = 0; i < 3; i++) {
        printf("CRC32(\"%s\") = 0x%08X\n", test_strings[i], calculate_crc32(test_strings[i]));
    }
    
    return 0;
}
