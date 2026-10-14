#include <stdio.h>

void logger(char *param_1) {
    printf(param_1);
    putchar(10);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    } else {
        printf("[log] ");
        logger(argv[1]);
    }
    return argc < 2;
}
