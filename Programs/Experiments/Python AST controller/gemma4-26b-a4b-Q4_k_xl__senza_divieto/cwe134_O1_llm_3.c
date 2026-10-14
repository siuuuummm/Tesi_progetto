#include <stdio.h>

void print_msg_with_newline(char *msg) {
    printf(msg);
    putchar(10);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
        return 1;
    } else {
        printf("[log] ");
        print_msg_with_newline(argv[1]);
        return 0;
    }
}
