#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Funzione di cifratura XOR su array di byte
void xor_cipher(uint8_t *data, int len, uint8_t key) {
    if (len > 0) {
        uint8_t *end = data + len;
        while (data != end) {
            *data ^= key;
            data++;
        }
    }
}

// Rotate left su 32 bit
uint32_t rol32(uint32_t value, uint8_t shift) {
    return (value << (shift & 0x1f)) | (value >> (32 - (shift & 0x1f)));
}

// Checksum custom: somma e rotazione per ogni byte
uint32_t custom_checksum(uint8_t *data, int len) {
    uint32_t result = 0;
    if (len > 0) {
        uint8_t *end = data + len;
        do {
            result += *data;
            result = (result << 3) | (result >> 29);
            data++;
        } while (data != end);
        return result;
    }
    return 0;
}

int main(void) {
    char buffer[23];
    strncpy(buffer, "secret message", 0xf);
    
    size_t msg_len = strlen(buffer);

    uint32_t checksum_originale = custom_checksum((uint8_t *)buffer, (int)msg_len);
    printf("Checksum originale: %u\n", checksum_originale);
    
    xor_cipher((uint8_t *)buffer, (int)msg_len, 0x5A);
    uint32_t checksum_cifrato = custom_checksum((uint8_t *)buffer, (int)msg_len);
    printf("Checksum cifrato:   %u\n", checksum_cifrato);
    
    xor_cipher((uint8_t *)buffer, (int)msg_len, 0x5A);
    printf("Decifrato: %s\n", buffer);
    
    return 0;
}
