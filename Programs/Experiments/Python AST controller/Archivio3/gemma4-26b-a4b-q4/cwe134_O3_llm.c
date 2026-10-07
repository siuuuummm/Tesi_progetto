#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
        return 1;
    } else {
        printf("[log] ");
        printf(argv[1]);
        putchar(10);
        return 0;
    }
}
