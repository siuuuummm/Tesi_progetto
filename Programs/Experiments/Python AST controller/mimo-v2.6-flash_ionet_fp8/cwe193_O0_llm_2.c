#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
 * FUN_004004b6 (register_name):
 * se strlen(name) < 0x11 alloca 0x10 byte e copia con strcpy,
 * altrimenti restituisce NULL.
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
        dest = NULL;
    }
    return dest;
}

int main(int argc, char **argv)
{
    char *s;
    size_t len;
    int i;

    setvbuf(stdout, NULL, 2, 0);
    for (i = 1; i < argc; i = i + 1) {
        s = register_name(argv[i]);
        if (s == NULL) {
            len = strlen(argv[i]);
            printf("Nome troppo lungo: %zu caratteri\n", len);
        } else {
            len = strlen(s);
            printf("Registrato: %s (%zu caratteri)\n", s, len);
            free(s);
        }
    }
    return 0;
}
