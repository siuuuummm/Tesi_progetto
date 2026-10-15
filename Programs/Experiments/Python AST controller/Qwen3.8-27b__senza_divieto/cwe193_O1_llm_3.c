#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * FUN_004004b6
 * Reads the input string, computes its length and, if the length is
 * strictly less than 0x11 (17), allocates a 0x10 (16) byte buffer and
 * copies the whole string (including the terminating '\0') into it with
 * strcpy. Returns the allocated buffer, or NULL when the name is too long.
 *
 * NOTE (faithful to the binary, not "fixed"): a 16-character string
 * (length == 0x10) passes the `len < 0x11` test, yet strcpy writes 17
 * bytes into the 16-byte buffer, overflowing the heap allocation by one
 * byte.
 */
char *register_name(char *s)
{
    size_t len;
    char *dest;

    len = strlen(s);
    dest = (char *)0x0;
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, s);
    }
    return dest;
}

/*
 * FUN_004004f1 (main)
 *
 * setvbuf(stdout, NULL, 2, 0)          -> unbuffered stdout
 * for each argument after the program name (argv[1] .. argv[argc-1]):
 *     register the argument;
 *     - if registration failed (name too long):
 *         printf("Nome troppo lungo: %zu caratteri\n", strlen(arg));
 *     - otherwise:
 *         printf("Registrato: %s (%zu caratteri)\n", result, strlen(result));
 *         free(result);
 */
int main(int argc, char **argv)
{
    char **p;
    char *arg;
    char *result;

    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        p = (char **)(argv + 1);
        do {
            arg = *p;
            result = register_name(arg);
            if (result == (char *)0x0) {
                printf("Nome troppo lungo: %zu caratteri\n", strlen(arg));
            }
            else {
                printf("Registrato: %s (%zu caratteri)\n", result, strlen(result));
                free(result);
            }
            p = p + 1;
        } while (p != (char **)(argv + 0x2 + (argc - 2)));
    }
    return 0;
}
