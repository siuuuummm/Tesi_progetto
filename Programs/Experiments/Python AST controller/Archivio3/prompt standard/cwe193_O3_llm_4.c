#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * FUN_004005e0 - helper di copia nome (versione out-of-line, inlinata nel main da -O3).
 * Copia la stringa in un buffer heap di 0x10 byte; restituisce NULL se troppo lunga.
 */
static char *copia_nome(const char *s)
{
    size_t len;
    char *dst;

    len = strlen(s);
    dst = (char *)0x0;
    if (len < 0x11) {
        dst = (char *)malloc(0x10);
        /* copia len + 1 byte (terminatore incluso), come nel decompilato */
        strcpy(dst, s);
    }
    return dst;
}

/*
 * FUN_004003c0 - main.
 * Registra ogni argomento (argv[1..argc-1]): se la lunghezza supera 0x10 segnala
 * "nome troppo lungo", altrimenti lo copia in un buffer heap e lo stampa.
 */
int main(int argc, char **argv)
{
    int i;

    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        for (i = 1; i < argc; i++) {
            size_t s = strlen(argv[i]);
            char *ptr;

            if (0x10 < s) {
                printf("Nome troppo lungo: %zu caratteri\n", s);
                continue;
            }
            ptr = (char *)malloc(0x10);
            /* copia s + 1 byte (terminatore incluso) nel buffer da 0x10 */
            strcpy(ptr, argv[i]);
            printf("Registrato: %s (%zu caratteri)\n", ptr, s);
            free(ptr);
        }
    }
    return 0;
}
