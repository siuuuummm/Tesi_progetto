#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Decompiled from test_O0 (stripped x86-64) - original at 0x004004b6.
 *
 * Behaviour observed in the binary:
 *   - measure the input length
 *   - if the length is <= 0x10 (16): allocate 0x10 (16) bytes and copy the
 *     whole string with strcpy
 *   - otherwise return NULL
 *
 * Note: for a string of length 16, strcpy writes 17 bytes (16 + NUL) into the
 * 16-byte allocation. This overflow is reproduced faithfully as found in the
 * original binary and is intentionally NOT "fixed".
 */
char *register_name(char *name)
{
    size_t len;
    char *dest;

    len = strlen(name);
    if (len <= 0x10) {
        dest = (char *)malloc(0x10);
        strcpy(dest, name);
    }
    else {
        dest = (char *)0x0;
    }
    return dest;
}

/*
 * Decompiled from test_O0 (stripped x86-64) - original main at 0x00400507.
 *
 * For every argument (from argv[1]) it attempts to "register" the name:
 *   - on success (non-NULL): print the registered name and its length, free it
 *   - on failure (NULL):     print that the name is too long with its length
 */
int main(int argc, char **argv)
{
    char *name;
    size_t len;
    int i;

    setvbuf(stdout, (char *)0x0, 2, 0);
    for (i = 1; i < argc; i = i + 1) {
        name = register_name(argv[i]);
        if (name == (char *)0x0) {
            len = strlen(argv[i]);
            printf("Nome troppo lungo: %zu caratteri\n", len);
        }
        else {
            len = strlen(name);
            printf("Registrato: %s (%zu caratteri)\n", name, len);
            free(name);
        }
    }
    return 0;
}
