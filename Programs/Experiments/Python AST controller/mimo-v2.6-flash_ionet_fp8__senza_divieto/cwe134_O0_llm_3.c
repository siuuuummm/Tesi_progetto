#include <stdio.h>

/* FUN_00400476: stampa la stringa seguita da newline */
static void print_message(const char *msg)
{
    printf(msg);
    putchar(10);
}

/* FUN_004004a0: main */
int main(int argc, long argv_long)
{
    char **argv = (char **)argv_long;

    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    } else {
        printf("[log] ");
        print_message(argv[1]);
    }
    return argc < 2;
}