#include <stdio.h>
#include <stdbool.h>

void print_message(const char *msg)
{
    printf(msg);
    putchar(10);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    }
    else {
        printf("[log] ");
        printf(argv[1]);
        putchar(10);
    }
    return argc < 2;
}
