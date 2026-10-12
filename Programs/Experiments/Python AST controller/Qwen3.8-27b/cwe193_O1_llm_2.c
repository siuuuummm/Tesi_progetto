#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Original name: FUN_004004b6
 * Copies a name into a fixed 16-byte buffer when its length is < 17,
 * otherwise returns NULL.
 */
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

/* Original name: FUN_004004f1 (main) */
int main(int argc, char **argv)
{
    char *s;
    char *result;
    size_t len;
    char **p;

    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        p = &argv[1];
        do {
            s = *p;
            result = register_name(s);
            if (result == (char *)0x0) {
                len = strlen(s);
                printf("Nome troppo lungo: %zu caratteri\n", len);
            }
            else {
                len = strlen(result);
                printf("Registrato: %s (%zu caratteri)\n", result, len);
                free(result);
            }
            p = p + 1;
        } while (p != &argv[argc]);
    }
    return 0;
}
