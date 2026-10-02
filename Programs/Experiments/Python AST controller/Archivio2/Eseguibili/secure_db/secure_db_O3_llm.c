#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encode_data(char *data) {
    while (*data != '\0') {
        *data = (*data ^ 0x5a) + 1;
        data++;
    }
}

void decode_data(char *data) {
    while (*data != '\0') {
        *data = (*data - 1) ^ 0x5a;
        data++;
    }
}

int main(int argc, char **argv) {
    int *record;
    char *data_ptr;

    if (argc > 1) {
        record = (int *)malloc(0x30);
        if (!record) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        record[0] = -0x21524111;
        data_ptr = (char *)(record + 1);
        strncpy(data_ptr, argv[1], 0x1f);
        data_ptr[0x1f] = '\0';
        /* Codifica il dato */
        encode_data(data_ptr);
        if (((record[0] >> 4) & 0xffU) > 0x10) {
            puts("Record protetto creato.");
        }
        /* Decodifica il dato (riporta al valore originale) */
        decode_data(data_ptr);
        printf("Dato originale: %s\n", data_ptr);
        free(record);
        return 0;
    }
    return 1;
}
