#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Funzione chiamata dal main per ogni argomento.
 * Se la stringa è più corta di 0x11 (17) caratteri, alloca 0x10 (16)
 * byte e vi copia la stringa; altrimenti ritorna NULL.
 */
char *register_name(char *name)
{
    size_t len;
    char *dest;

    len = strlen(name);
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, name);
    } else {
        dest = (char *)0x0;
    }
    return dest;
}

int main(int argc, long argv)
{
    char *s;
    size_t len;
    int i;

    setvbuf(stdout, (char *)0x0, 2, 0);
    for (i = 1; i < argc; i = i + 1) {
        s = register_name(*(char **)(argv + (long)i * 8));
        if (s == (char *)0x0) {
            len = strlen(*(char **)(argv + (long)i * 8));
            printf("Nome troppo lungo: %zu caratteri\n", len);
        } else {
            len = strlen(s);
            printf("Registrato: %s (%zu caratteri)\n", s, len);
            free(s);
        }
    }
    return 0;
}
