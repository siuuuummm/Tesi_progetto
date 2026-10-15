#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    setvbuf(stdout, (char *)0, 2, 0);
    if (1 < argc) {
        char **begin = (char **)(argv + 1);
        char **end   = (char **)(argv + argc);
        do {
            char *s = *begin;
            size_t len = strlen(s);
            if (0x10 < len) {
                begin = begin + 1;
                printf("Nome troppo lungo: %zu caratteri\n", len);
                continue;
            }
            char *buf = (char *)malloc(0x10);
            size_t n = len + 1;
            if (n < 8) {
                if ((n & 4) == 0) {
                    if (n != 0) {
                        *(char *)buf = *(char *)s;
                        if ((n & 2) != 0) {
                            *(uint16_t *)(buf + (n - 2)) = *(uint16_t *)(s + (n - 2));
                        }
                    }
                }
                else {
                    *(uint32_t *)buf = *(uint32_t *)s;
                    *(uint32_t *)(buf + (n - 4)) = *(uint32_t *)(s + (n - 4));
                }
            }
            else {
                *(uint64_t *)(buf + (n - 8)) = *(uint64_t *)(s + (n - 8));
                if (7 < (n - 1)) {
                    size_t i = 0;
                    size_t j;
                    do {
                        j = i + 8;
                        *(uint64_t *)(buf + i) = *(uint64_t *)(s + i);
                        i = j;
                    } while (j < ((n - 1) & 0xfffffffffffffff8));
                }
            }
            printf("Registrato: %s (%zu caratteri)\n", buf, len);
            begin = begin + 1;
            free(buf);
        } while (begin != end);
    }
    return 0;
}
