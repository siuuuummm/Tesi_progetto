#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char data[32];
    void (*process)(char*);
} Record;

void obfuscate(char* s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = (s[i] ^ 0x5A) + 1;
    }
}

void reveal(char* s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = (s[i] - 1) ^ 0x5A;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;

    Record* reg = (Record*)malloc(sizeof(Record));
    reg->id = 0xDEADBEEF;
    strncpy(reg->data, argv[1], 31);
    reg->process = obfuscate;

    // Esegue la trasformazione tramite puntatore a funzione
    reg->process(reg->data);

    // Simulazione di logica condizionale complessa
    int check = (reg->id >> 4) & 0xFF;
    if (check > 0x10) {
        printf("Record protetto creato.\n");
    }

    // Ripristino
    reg->process = reveal;
    reg->process(reg->data);

    printf("Dato originale: %s\n", reg->data);

    free(reg);
    return 0;
}
