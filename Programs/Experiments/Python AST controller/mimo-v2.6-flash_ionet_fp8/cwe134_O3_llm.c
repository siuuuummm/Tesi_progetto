#include <stdio.h>
#include <stdint.h>

void print_line(char *msg)
{
    printf(msg);
    putchar(10);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
        return 1;
    }
    printf("[log] ");
    printf(argv[1]);
    putchar('\n');
    return 0;
}