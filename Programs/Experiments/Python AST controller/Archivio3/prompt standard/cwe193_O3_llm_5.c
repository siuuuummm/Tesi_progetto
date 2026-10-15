#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    char **s;
    char *dst;
    size_t len;

    setvbuf(stdout, (char *)0x0, 2, 0);

    if (1 < argc) {
        s = argv + 1;
        for (; s != argv + argc; s++) {
            len = strlen(*s);
            if (0x10 < len) {
                printf("Nome troppo lungo: %zu caratteri\n", len);
                continue;
            }
            dst = (char *)malloc(0x10);
            memcpy(dst, *s, len + 1);
            printf("Registrato: %s (%zu caratteri)\n", dst, len);
            free(dst);
        }
    }
    return 0;
}
