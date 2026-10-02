#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Codifica "protetta": ogni byte viene XORato con 0x5A e incrementato di 1
void encode_record(char *data) {
    unsigned char b;
    while ((b = (unsigned char)(*data)) != 0) {
        *data = (b ^ 0x5A) + 1;
        data++;
    }
}

// Decodifica: operazione inversa rispetto alla codifica
void decode_record(char *data) {
    unsigned char b;
    while ((b = (unsigned char)(*data)) != 0) {
        *data = (b - 1) ^ 0x5A;
        data++;
    }
}

int main(int argc, char **argv) {
    if (argc > 1) {
        int *record = (int *)malloc(0x30);
        if (!record) {
            printf("Errore malloc\n");
            return 1;
        }
        record[0] = -0x21524111;
        char *data = (char *)(record + 1);
        strncpy(data, argv[1], 0x1F);
        data[0x1F] = '\0'; // Assicuriamo terminazione

        // Codifica
        encode_record(data);
        if (((unsigned int)record[0] >> 4 & 0xFFU) > 0x10) {
            puts("Record protetto creato.");
        }

        // Decodifica e mostra il dato originale
        decode_record(data);
        printf("Dato originale: %s\n", data);
        free(record);
        return 0;
    }
    return 1;
}