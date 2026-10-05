#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char **p;
    char **end;
    char *s;
    size_t len;
    char *dst;
    unsigned int n;
    unsigned long i;
    int next;

    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        p = (char **)(argv + 1);
        end = (char **)(argv + 2 + (unsigned long)(argc - 2));
        do {
            for (;;) {
                s = *p;
                len = strlen(s);
                if (0x10 < len) break;
                dst = (char *)malloc(0x10);
                n = len + 1;
                if (n < 8) {
                    if ((n & 4) == 0) {
                        if ((n != 0) && (*dst = *s, (n & 2) != 0)) {
                            *(uint16_t *)(dst + (n - 2)) = *(uint16_t *)(s + (n - 2));
                        }
                    }
                    else {
                        *(uint32_t *)dst = *(uint32_t *)s;
                        *(uint32_t *)(dst + (n - 4)) = *(uint32_t *)(s + (n - 4));
                    }
                }
                else {
                    *(uint64_t *)(dst + (n - 8)) = *(uint64_t *)(s + (n - 8));
                    if (7 < n - 1) {
                        i = 0;
                        do {
                            next = (int)i + 8;
                            *(uint64_t *)(dst + i) = *(uint64_t *)(s + i);
                            i = (unsigned long)next;
                        } while (next < ((n - 1) & 0xfffffff8));
                    }
                }
                printf("Registrato: %s (%zu caratteri)\n", dst, len);
                p = p + 1;
                free(dst);
                if (p == end) {
                    return 0;
                }
            }
            p = p + 1;
            printf("Nome troppo lungo: %zu caratteri\n", len);
        } while (p != end);
    }
    return 0;
}
