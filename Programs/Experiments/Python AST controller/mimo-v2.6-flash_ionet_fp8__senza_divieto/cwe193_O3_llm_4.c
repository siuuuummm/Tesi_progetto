#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
 * copia_nome (FUN_004005e0):
 * restituisce una copia allocata della stringa se la sua lunghezza
 * e' minore di 0x11, altrimenti restituisce NULL.
 */
char *copia_nome(char *nome)
{
    size_t len;
    char *dest;

    len = strlen(nome);
    dest = NULL;
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, nome);
    }
    return dest;
}

/*
 * main (FUN_004003c0):
 * disabilita il buffering di stdout, poi per ogni argomento:
 *   - lunghezza > 0x10 -> "Nome troppo lungo"
 *   - altrimenti copia in un buffer di 0x10 byte, stampa e libera
 */
int main(int argc, char **argv)
{
    char *s;
    char *p;
    size_t len;
    int i;

    setvbuf(stdout, NULL, 2, 0);
    if (1 < argc) {
        for (i = 1; i < argc; i++) {
            s = argv[i];
            len = strlen(s);
            if (0x10 < len) {
                printf("Nome troppo lungo: %zu caratteri\n", len);
            } else {
                p = (char *)malloc(0x10);
                strcpy(p, s);
                printf("Registrato: %s (%zu caratteri)\n", p, len);
                free(p);
            }
        }
    }
    return 0;
}