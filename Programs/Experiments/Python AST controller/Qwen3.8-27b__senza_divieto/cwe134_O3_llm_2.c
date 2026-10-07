#include <stdio.h>

/* Decompiled from 0x004004e0: prints its string argument, then a newline. */
void print_line(char *s)
{
    printf(s);
    putchar(10);
}

/* Decompiled from 0x00400390 (main). */
int main(int argc, char *argv[])
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
