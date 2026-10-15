#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * FUN_004004b6
 *
 * Allocates a 16-byte (0x10) heap buffer and copies the given string into it
 * using strcpy. The string is only accepted when its length (strlen) is less
 * than 0x11 (17); otherwise NULL is returned. Note: for a 16-character input
 * (strlen == 0x10) strcpy writes strlen+1 == 17 bytes into a 16-byte buffer.
 */
char *register_name(char *name)
{
    size_t len;
    char *dest;

    len = strlen(name);
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, name);
    }
    else {
        dest = (char *)0x0;
    }
    return dest;
}

/*
 * FUN_00400507 (main)
 *
 * For every command-line argument (starting with argv[1]) it tries to register
 * the name. If registration fails (string too long) it prints the offending
 * length; otherwise it prints the registered name and its length, then frees
 * the allocated buffer.
 */
int main(int argc, char **argv)
{
    char *s;
    size_t len;
    int c;

    setvbuf(stdout, (char *)0x0, 2, 0);
    for (c = 1; c < argc; c = c + 1) {
        s = register_name(argv[c]);
        if (s == (char *)0x0) {
            len = strlen(argv[c]);
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
