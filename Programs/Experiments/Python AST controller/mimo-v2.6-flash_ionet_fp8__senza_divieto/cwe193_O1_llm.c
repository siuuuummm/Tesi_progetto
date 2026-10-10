#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Copia il nome solo se la sua lunghezza e' minore di 0x11 (17).
   Alloca esattamente 0x10 (16) byte. Ritorna NULL se il nome e' troppo lungo. */
static char *duplicate_short_name(const char *name)
{
    size_t len;
    char *dest;

    len = strlen(name);
    dest = NULL;
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, name);
    }
    return dest;
}

int main(int argc, char **argv)
{
    char *arg;
    char *copy;
    size_t len;

    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        char **p = (char **)((char *)argv + 0x8);
        char **end = (char **)((char *)argv + 0x10 + (size_t)(argc - 2) * 0x8);

        do {
            arg = (char *)*p;
            copy = duplicate_short_name(arg);
            if (copy == (char *)0x0) {
                len = strlen(arg);
                printf("Nome troppo lungo: %zu caratteri\n", len);
            } else {
                len = strlen(copy);
                printf("Registrato: %s (%zu caratteri)\n", copy, len);
                free(copy);
            }
            p = p + 1;
        } while (p != end);
    }
    return 0;
}
