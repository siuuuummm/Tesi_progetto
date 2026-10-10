#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* FUN_004004b6: copia il nome solo se la lunghezza e' strettamente minore
   di 0x11 (17); altrimenti ritorna NULL. Alloca esattamente 0x10 byte. */
char *register_name(char *name)
{
    size_t len;
    char *dest;

    len = strlen(name);
    dest = (char *)0x0;
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, name);
    }
    return dest;
}

/* FUN_004004f1: main */
int main(int argc, char **argv)
{
    char *name;
    char *copy;
    size_t len;
    char **p;

    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        p = (char **)(argv + 1);
        do {
            name = *p;
            copy = register_name(name);
            if (copy == (char *)0x0) {
                len = strlen(name);
                printf("Nome troppo lungo: %zu caratteri\n", len);
            } else {
                len = strlen(copy);
                printf("Registrato: %s (%zu caratteri)\n", copy, len);
                free(copy);
            }
            p = p + 1;
        } while (p != (char **)((char *)argv + 0x10 + (unsigned long)(argc - 2) * 8));
    }
    return 0;
}
