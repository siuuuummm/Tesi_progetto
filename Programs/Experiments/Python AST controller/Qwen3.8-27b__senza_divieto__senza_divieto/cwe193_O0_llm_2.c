#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* FUN_004004b6: se la stringa ha meno di 0x11 caratteri la duplica
 * in un buffer di 0x10 byte, altrimenti restituisce NULL. */
static char *clone_if_short(const char *src)
{
    size_t len;
    char *dst;

    len = strlen(src);
    if (len < 0x11) {
        dst = (char *)malloc(0x10);
        strcpy(dst, src);
    }
    else {
        dst = (char *)0x0;
    }
    return dst;
}

int main(int argc, char **argv)
{
    char *s;
    size_t len;
    int i;

    setvbuf(stdout, (char *)0x0, 2, 0);
    for (i = 1; i < argc; i = i + 1) {
        s = clone_if_short(argv[i]);
        if (s == (char *)0x0) {
            len = strlen(argv[i]);
            printf("Nome troppo lungo: %zu caratteri\n", len);
        }
        else {
            len = strlen(s);
            printf("Registrato: %s (%zu caratteri)\n", s, len);
            free(s);
        }
    }
    return 0;
}
