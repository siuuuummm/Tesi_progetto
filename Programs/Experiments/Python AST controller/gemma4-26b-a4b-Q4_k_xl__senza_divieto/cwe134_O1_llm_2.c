#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void logger(char *msg) {
    printf(msg);
    putchar(10);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    } else {
        printf("[log] ");
        logger(argv[1]);
    }
    return (argc < 2);
}
