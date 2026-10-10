#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FUN_004004b6: duplica la stringa in ingresso se la sua lunghezza è
 * strettamente minore di 0x11 (17) caratteri, allocando un buffer di
 * 0x10 (16) byte. Altrimenti restituisce NULL. */
static char *register_name(const char *name)
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

/* FUN_00400507: entry point dichiarato come main. */
int main(int argc, char **argv)
{
    char *reg;
    size_t len;
    int i;

    setvbuf(stdout, (char *)0x0, 2, 0);
    for (i = 1; i < argc; i = i + 1) {
        reg = register_name(argv[i]);
        if (reg == (char *)0x0) {
            len = strlen(argv[i]);
            printf("Nome troppo lungo: %zu caratteri\n", len);
        } else {
            len = strlen(reg);
            printf("Registrato: %s (%zu caratteri)\n", reg, len);
            free(reg);
        }
    }
    return 0;
}
