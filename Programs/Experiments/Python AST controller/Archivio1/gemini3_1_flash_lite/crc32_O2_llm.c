#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* CRC32 lookup table */
uint32_t crc32_table[256];

/* Function to initialize the CRC32 table */
void init_crc32_table(void) {
    for (uint32_t i = 0; i < 256; i++) {
        uint32_t crc = i;
        
        // Bit reversal logic observed in FUN_00400560
        crc = ((crc & 0xffff0000) >> 16) | ((crc & 0x0000ffff) << 16);
        crc = ((crc & 0xff00ff00) >> 8) | ((crc & 0x00ff00ff) << 8);
        crc = ((crc & 0xf0f0f0f0) >> 4) | ((crc & 0x0f0f0f0f) << 4);
        crc = ((crc & 0xcccccccc) >> 2) | ((crc & 0x33333333) << 2);
        crc = ((crc & 0xaaaaaaaa) >> 1) | ((crc & 0x55555555) << 1);

        for (int j = 0; j < 8; j++) {
            if (crc & 0x80000000) {
                crc = (crc << 1) ^ 0x04c11db7; // Standard CRC32 polynomial
            } else {
                crc <<= 1;
            }
        }
        
        // Final bit reversal
        crc = ((crc & 0xffff0000) >> 16) | ((crc & 0x0000ffff) << 16);
        crc = ((crc & 0xff00ff00) >> 8) | ((crc & 0x00ff00ff) << 8);
        crc = ((crc & 0xf0f0f0f0) >> 4) | ((crc & 0x0f0f0f0f) << 4);
        crc = ((crc & 0xcccccccc) >> 2) | ((crc & 0x33333333) << 2);
        crc = ((crc & 0xaaaaaaaa) >> 1) | ((crc & 0x55555555) << 1);
        
        crc32_table[i] = crc;
    }
}

/* Function to calculate CRC32 */
uint32_t calculate_crc32(const char *str) {
    uint32_t crc = 0xFFFFFFFF;
    size_t len = strlen(str);
    
    for (size_t i = 0; i < len; i++) {
        uint8_t byte = (uint8_t)str[i];
        crc = (crc >> 8) ^ crc32_table[(byte ^ crc) & 0xFF];
    }
    
    return ~crc;
}

int main(void) {
    init_crc32_table();
    
    const char *strings[] = {
        "",
        "Hello",
        "World",
        "Hello World"
    };
    
    for (int i = 0; i < 4; i++) {
        printf("CRC32(\"%s\") = 0x%08X\n", strings[i], calculate_crc32(strings[i]));
    }
    
    return 0;
}
