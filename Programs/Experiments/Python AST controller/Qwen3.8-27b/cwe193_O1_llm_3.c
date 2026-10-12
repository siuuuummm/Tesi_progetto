#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static char *register_name(char *s)
{
    size_t len;
    char *dest;

    len = strlen(s);
    dest = NULL;
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, s);
    }
    return dest;
}

int main(int argc, char **argv)
{
    char **p;
    char *name;
    char *registered;
    size_t len;

    setvbuf(stdout, NULL, 2, 0);
    if (argc > 1) {
        p = argv + 1;
        do {
            name = *p;
            registered = register_name(name);
            if (registered == NULL) {
                len = strlen(name);
                printf("Nome troppo lungo: %zu caratteri\n", len);
            }
            else {
                len = strlen(registered);
                printf("Registrato: %s (%zu caratteri)\n", registered, len);
                free(registered);
            }
            p = p + 1;
        } while (p != argv + 2 + (argc - 2));
    }
    return 0;
}
