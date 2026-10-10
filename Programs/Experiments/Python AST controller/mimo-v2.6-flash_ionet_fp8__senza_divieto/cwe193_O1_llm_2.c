#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* FUN_004004b6: copia il nome in un buffer di 16 byte solo se lunghezza < 0x11 */
static char *register_name(const char *name)
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

/* FUN_004004f1: main */
int main(int argc, char **argv)
{
    const char *arg;
    char *registered;
    size_t len;
    char **p;

    setvbuf(stdout, NULL, 2, 0);
    if (1 < argc) {
        p = argv + 1;
        do {
            arg = *p;
            registered = register_name(arg);
            if (registered == NULL) {
                len = strlen(arg);
                printf("Nome troppo lungo: %zu caratteri\n", len);
            } else {
                len = strlen(registered);
                printf("Registrato: %s (%zu caratteri)\n", registered, len);
                free(registered);
            }
            p = p + 1;
        } while (p != argv + (argc - 2) + 2);
    }
    return 0;
}
