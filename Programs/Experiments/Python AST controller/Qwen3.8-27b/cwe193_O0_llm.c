#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FUN_004004b6
 * Allocates a 0x10 (16) byte buffer and copies the name string into it.
 * Returns the allocated pointer if strlen(name) <= 0x10, otherwise NULL.
 */
static char *copia_nome(char *name)
{
    size_t len;
    char *dest;

    len = strlen(name);
    if (len <= 0x10) {
        dest = (char *)malloc(0x10);
        strcpy(dest, name);
    }
    else {
        dest = (char *)0;
    }
    return dest;
}

/* FUN_00400507 */
int main(int argc, char **argv)
{
    int i;
    char *s;
    size_t len;

    setvbuf(stdout, (char *)0, 2, 0);
    for (i = 1; i < argc; i = i + 1) {
        s = copia_nome(argv[i]);
        if (s == (char *)0) {
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
