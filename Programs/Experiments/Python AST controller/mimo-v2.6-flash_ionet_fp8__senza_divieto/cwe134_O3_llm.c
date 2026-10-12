#include <stdio.h>

/* FUN_004004e0: stampa la stringa e va a capo */
void print_line(char *msg)
{
    printf(msg);
    putchar(10);
}

/* FUN_00400390: main, entry point passato a __libc_start_main da entry */
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