/* xor_cipher.c — Difficolta: MEDIA
 * Cifrario XOR + checksum. Operazioni bitwise che i decompilatori
 * gestiscono in modo variabile (shift, and, or, xor). */
#include <stdio.h>
#include <string.h>

void xor_encrypt(unsigned char *data, int len, unsigned char key) {
    for (int i = 0; i < len; i++)
        data[i] ^= key;
}

unsigned int rotate_left(unsigned int x, int n) {
    return (x << n) | (x >> (32 - n));
}

unsigned int simple_checksum(const unsigned char *data, int len) {
    unsigned int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += data[i];
        sum = rotate_left(sum, 3);
    }
    return sum;
}

int main(void) {
    unsigned char msg[] = "secret message";
    int len = (int)strlen((char *)msg);
    unsigned char key = 0x5A;

    printf("Checksum originale: %u\n", simple_checksum(msg, len));

    xor_encrypt(msg, len, key);
    printf("Checksum cifrato:   %u\n", simple_checksum(msg, len));

    xor_encrypt(msg, len, key);  /* decifra */
    printf("Decifrato: %s\n", msg);

    return 0;
}
