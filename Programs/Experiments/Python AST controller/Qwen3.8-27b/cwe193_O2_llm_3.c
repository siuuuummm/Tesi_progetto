#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        char **ptr = (char **)(argv + 1);
        char **end = (char **)(argv + argc);
        char *s;
        char *dst;
        size_t len;

        do {
            while (1) {
                s = *ptr;
                len = strlen(s);
                if (0x10 < len)
                    break;
                dst = (char *)malloc(0x10);
                strcpy(dst, s);
                printf("Registrato: %s (%zu caratteri)\n", dst, len);
                ptr = ptr + 1;
                free(dst);
                if (ptr == end)
                    return 0;
            }
            ptr = ptr + 1;
            printf("Nome troppo lungo: %zu caratteri\n", len);
        } while (ptr != end);
    }
    return 0;
}
