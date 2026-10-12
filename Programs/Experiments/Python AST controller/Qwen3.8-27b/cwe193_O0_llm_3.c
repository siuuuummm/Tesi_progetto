#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Allocates a fixed-size buffer and copies the given name into it.
 * Returns the buffer on success, or NULL if the name is "too long".
 *
 * NOTE: The length check accepts names of up to 0x11 - 1 = 16 characters,
 * but only 0x10 = 16 bytes are allocated. A 16-character name therefore
 * overflows the allocation by one byte (the trailing null terminator).
 */
char *register_name(char *name)
{
    size_t len = strlen(name);
    char *dest;

    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, name);
    }
    else {
        dest = NULL;
    }

    return dest;
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    for (int i = 1; i < argc; i++) {
        char *s = register_name(argv[i]);
        size_t len;

        if (s == NULL) {
            len = strlen(argv[i]);
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
