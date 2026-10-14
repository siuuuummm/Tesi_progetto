#include <stdio.h>
#include <stdbool.h>

void print_with_newline(char *str) {
    printf(str);
    putchar('\n');
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
        return 1;
    } else {
        printf("[log] ");
        printf(argv[1]);
        putchar('\n');
        return 0;
    }
}
