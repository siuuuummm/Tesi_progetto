#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

void xor_cipher(uint8_t *data, int len, uint8_t key) {
    uint8_t *end;
    if (len > 0) {
        end = data + len;
        do {
            *data = *data ^ key;
            data = data + 1;
        } while (data != end);
    }
}

uint32_t rol32(uint32_t value, uint8_t shift) {
    return (value << (shift & 0x1f)) | (value >> (32 - (shift & 0x1f)));
}

uint32_t custom_checksum(uint8_t *data, int len) {
    uint32_t checksum;
    uint8_t *end;
    if (len > 0) {
        end = data + len;
        checksum = 0;
        do {
            checksum = ((checksum + *data) * 8) | ((checksum + *data) >> 29);
            data = data + 1;
        } while (data != end);
        return checksum;
    }
    return 0;
}

int main(void) {
    uint32_t chksum;
    size_t len;
    char buf[23];
    strncpy(buf, "secret message", 0xf);
    len = strlen(buf);
    chksum = custom_checksum((uint8_t *)buf, (int)len);
    printf("Checksum originale: %u\n", (unsigned long)chksum);
    xor_cipher((uint8_t *)buf, (int)len, 0x5a);
    chksum = custom_checksum((uint8_t *)buf, (int)len);
    printf("Checksum cifrato:   %u\n", (unsigned long)chksum);
    xor_cipher((uint8_t *)buf, (int)len, 0x5a);
    printf("Decifrato: %s\n", buf);
    return 0;
}
