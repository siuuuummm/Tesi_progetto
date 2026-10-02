#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RECORD_MAGIC -559038289 // 0xDEADC0DE
#define RECORD_DATA_LEN 0x1f

typedef struct {
    int magic;
    char data[RECORD_DATA_LEN];
    void (*coder)(char*);
} SecureRecord;

void protect_record(char *data) {
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] = (data[i] ^ 0x5a) + 1;
    }
}

void unlock_record(char *data) {
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] = (data[i] - 1U) ^ 0x5a;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }

    SecureRecord *record = malloc(sizeof(SecureRecord));
    record->magic = RECORD_MAGIC;
    strncpy(record->data, argv[1], RECORD_DATA_LEN - 1);
    record->data[RECORD_DATA_LEN-1] = '\0';
    record->coder = protect_record;
    record->coder(record->data);
    if (((record->magic >> 4) & 0xff) > 0x10) {
        puts("Record protetto creato.");
    }
    record->coder = unlock_record;
    record->coder(record->data);
    printf("Dato originale: %s\n", record->data);
    free(record);
    return 0;
}
