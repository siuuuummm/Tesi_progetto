#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FUN_004004b6: prende un nome; se la lunghezza e' < 0x11 (17)
 * alloca 0x10 (16) byte con malloc e vi copia la stringa con strcpy;
 * altrimenti restituisce NULL. */
char *register_name(const char *name)
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
    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        int i;
        for (i = 1; i < argc; i++) {
            const char *s = argv[i];
            char *reg = register_name(s);
            if (reg == (char *)0x0) {
                size_t len = strlen(s);
                printf("Nome troppo lungo: %zu caratteri\n", len);
            }
            else {
                size_t len = strlen(reg);
                printf("Registrato: %s (%zu caratteri)\n", reg, len);
                free(reg);
            }
        }
    }
    return 0;
}
