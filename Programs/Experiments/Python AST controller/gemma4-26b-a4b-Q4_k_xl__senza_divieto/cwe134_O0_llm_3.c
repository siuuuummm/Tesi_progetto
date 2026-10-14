#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void print_log_message(char *message) {
    printf(message);
    putchar(10);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
        return 1;
    } else {
        printf("[log] ");
        print_log_message(argv[1]);
        return 0;
    }
}
