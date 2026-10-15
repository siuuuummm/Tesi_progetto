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
            const char *s = *ptr;
            size_t len = strlen(s);

            if (0x10 < len) {
                printf("Nome troppo lungo: %zu caratteri\n", len);
                ptr++;
                continue;
            }

            char *dst = (char *)malloc(0x10);

            /* memcpy(dst, s, len + 1) - copia inclusa la terminazione null */
            memcpy(dst, s, len + 1);

            printf("Registrato: %s (%zu caratteri)\n", dst, len);

            free(dst);
            ptr++;
        } while (ptr != end);
    }

    return 0;
}
