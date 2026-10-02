#include <stdio.h>
#include <string.h>
#include <stdint.h>

uint32_t crc32_table[256];

void init_crc32_table(void) {
    uint32_t crc;
    for (int i = 0; i < 256; i++) {
        crc = (uint32_t)i;
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xedb88320;
            } else {
                crc = crc >> 1;
            }
        }
        crc32_table[i] = crc;
    }
}

uint32_t calculate_crc32(const char *data, size_t length) {
    uint32_t crc = 0xffffffff;
    for (size_t i = 0; i < length; i++) {
        uint8_t index = (uint8_t)(data[i] ^ (uint8_t)crc);
        crc = crc32_table[index] ^ (crc >> 8);
    }
    return ~crc;
}

int main(void) {
    init_crc32_table();
    const char *test_strings[] = {"", "a", "abc", "Hello, World!"};
    int num_strings = 4;
    for (int i = 0; i < num_strings; i++) {
        size_t len = strlen(test_strings[i]);
        uint32_t crc = calculate_crc32(test_strings[i], len);
        printf("CRC32(\"%s\") = 0x%08X\n", test_strings[i], crc);
    }
    return 0;
}
