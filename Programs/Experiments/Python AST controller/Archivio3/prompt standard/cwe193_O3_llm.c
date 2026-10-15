#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    setvbuf(stdout, (char *)0x0, 2, 0);

    if (1 < argc) {
        char **ptr = argv + 1;
        char **end = argv + argc;

        do {
            char *s = *ptr;
            size_t len = strlen(s);
            if (0x10 < len) {
                ptr = ptr + 1;
                printf("Nome troppo lungo: %zu caratteri\n", len);
            }
            else {
                char *dst = (char *)malloc(0x10);
                /* copy len + 1 bytes (including the null terminator) */
                memcpy(dst, s, len + 1);
                printf("Registrato: %s (%zu caratteri)\n", dst, len);
                ptr = ptr + 1;
                free(dst);
                if (ptr == end) {
                    return 0;
                }
            }
        } while (ptr != end);
    }
    return 0;
}
