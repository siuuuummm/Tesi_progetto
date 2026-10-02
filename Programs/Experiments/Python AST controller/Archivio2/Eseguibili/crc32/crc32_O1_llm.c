#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Global CRC32 table */
uint32_t crc32_table[256];

/* Initialize the CRC32 table */
void init_crc32_table() {
    uint32_t i, j;
    uint32_t crc;

    for (i = 0; i < 256; i++) {
        crc = i;
        for (j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xedb88320;
            } else {
                crc >>= 1;
            }
        }
        crc32_table[i] = crc;
    }
}

/* Calculate CRC32 for a given data buffer */
uint32_t crc32(const uint8_t *data, size_t length) {
    uint32_t crc = 0xffffffff;
    size_t i;

    for (i = 0; i < length; i++) {
        crc = (crc >> 8) ^ crc32_table[(crc ^ data[i]) & 0xff];
    }
    return ~crc;
}

int main() {
    init_crc32_table();
    
    char *test_strings[] = {"", "a", "abc", "Hello, World!"};
    
    for (int i = 0; i < 4; i++) {
        char *s = test_strings[i];
        uint32_t crc = crc32((const uint8_t *)s, strlen(s));
        printf("CRC32(\"%s\") = 0x%08X\n", s, crc);
    }
    
    return 0;
}
