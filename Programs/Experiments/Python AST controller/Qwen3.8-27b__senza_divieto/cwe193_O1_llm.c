#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

char *register_name(char *name)
{
    size_t len = strlen(name);
    char *dest = (char *)0x0;
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, name);
    }
    return dest;
}

int main(int argc, char **argv)
{
    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        char **p = argv + 1;
        do {
            char *s = *p;
            char *registered = (char *)register_name(s);
            if (registered == (char *)0x0) {
                size_t slen = strlen(s);
                printf("Nome troppo lungo: %zu caratteri\n", slen);
            }
            else {
                size_t slen = strlen(registered);
                printf("Registrato: %s (%zu caratteri)\n", registered, slen);
                free(registered);
            }
            p = p + 1;
        } while (p != (char **)((size_t)argv + 0x10 + (size_t)(argc - 2) * 8));
    }
    return 0;
}
