#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encode_buffer(unsigned char *buffer) {
    while (*buffer != 0) {
        *buffer = (*buffer ^ 0x5a) + 1;
        buffer++;
    }
}

void decode_buffer(unsigned char *buffer) {
    while (*buffer != 0) {
        *buffer = (*buffer - 1) ^ 0x5a;
        buffer++;
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        int *record = malloc(0x30);
        if (!record) {
            perror("malloc failed");
            return 1;
        }
        *record = -0x21524111; // Magic number
        int *dest = record + 1;
        strncpy((char *)dest, argv[1], 0x1f);
        void (*f)(unsigned char *) = encode_buffer;
        f((unsigned char *)dest);
        if (((*record >> 4) & 0xff) > 0x10) {
            puts("Record protetto creato.");
        }
        f = decode_buffer;
        f((unsigned char *)dest);
        printf("Dato originale: %s\n", (char *)dest);
        free(record);
        return 0;
    }
    return 1;
}
