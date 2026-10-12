#include <stdio.h>

int main(int argc, long argv_ptr)
{
    char **argv = (char **)argv_ptr;

    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    } else {
        printf("[log] ");
        printf(argv[1]);
        putchar(10);
    }
    return argc < 2;
}