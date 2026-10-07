#include <stdio.h>
#include <stdint.h>

void log_message(char *msg) {
    printf(msg);
    putchar(10);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
        return 1;
    } else {
        printf("[log] ");
        log_message(argv[1]);
        return 0;
    }
}
