#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Faithful reconstruction of the string-copy helper (FUN_004005e0).
 * Copies strlen(src)+1 bytes into a fresh 0x10-byte buffer.
 * Returns NULL when the source is longer than 0x10 (16) characters. */
static char *safe_copy_name(const char *src)
{
    size_t len = strlen(src);
    char *dst = (char *)0x0;

    if (len < 0x11) {
        dst = (char *)malloc(0x10);
        memcpy(dst, src, len + 1);
    }
    return dst;
}

int main(int argc, char **argv)
{
    setvbuf(stdout, (char *)0x0, 2, 0);

    if (1 < argc) {
        char **arg_begin = (char **)(argv + 1);
        char **arg_end   = (char **)(argv + 2 + (size_t)(argc - 2));

        do {
            const char *s = *arg_begin;
            size_t len = strlen(s);
            char *dup;

            if (0x10 < len) {
                arg_begin = arg_begin + 1;
                printf("Nome troppo lungo: %zu caratteri\n", len);
                continue;
            }

            dup = (char *)malloc(0x10);
            memcpy(dup, s, len + 1);

            printf("Registrato: %s (%zu caratteri)\n", dup, len);
            arg_begin = arg_begin + 1;
            free(dup);
        } while (arg_begin != arg_end);
    }
    return 0;
}
