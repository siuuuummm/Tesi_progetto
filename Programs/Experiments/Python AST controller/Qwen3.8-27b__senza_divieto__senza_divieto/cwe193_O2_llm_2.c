#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * Ricostruzione fedele del binario stripped "test_O2".
 *
 * Il programma riceve una lista di "nomi" come argomenti della riga di comando
 * (a partire da argv[1]). Per ogni nome calcola la lunghezza: se supera i 16
 * caratteri (0x10) viene segnalato come troppo lungo, altrimenti il nome viene
 * copiato in un buffer di 0x10 byte allocato dinamicamente (duplica_nome) e
 * stampato, poi il buffer viene liberato.
 */

/*
 * Corrisponde a FUN_004005e0.
 * Alloca un buffer di 0x10 byte e vi copia strlen(s)+1 byte da s,
 * ma solo se strlen(s) < 0x11 (cioe' lunghezza <= 16).
 * In caso contrario restituisce NULL.
 */
static char *duplica_nome(const char *s)
{
    size_t len;
    char *dst;

    len = strlen(s);
    dst = (char *)0x0;
    if (len < 0x11) {
        dst = (char *)malloc(0x10);
        if (dst != (char *)0x0)
            memcpy(dst, s, len + 1);
    }
    return dst;
}

int main(int argc, char **argv)
{
    char **p;
    char *s;
    size_t len;
    char *buf;
    char **end;

    setvbuf(stdout, (char *)0x0, 2, 0);

    if (1 < argc) {
        p = argv + 1;
        end = argv + argc;

        while (p != end) {
            s = *p;
            len = strlen(s);
            if (0x10 < len) {
                printf("Nome troppo lungo: %zu caratteri\n", len);
                p = p + 1;
                continue;
            }

            buf = duplica_nome(s);
            printf("Registrato: %s (%zu caratteri)\n", buf, len);
            free(buf);
            p = p + 1;
        }
    }
    return 0;
}
