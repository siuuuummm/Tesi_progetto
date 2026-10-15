#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    char *s;
    size_t len;
    char *dst;

    setvbuf(stdout, (char *)0x0, 2, 0);

    if (1 < argc) {
        char **ptr = (char **)(argv + 1);
        char **end = (char **)(argv + argc);

        do {
            while (1) {
                s = (char *)*ptr;
                len = strlen(s);
                if (0x10 < len)
                    break;
                dst = (char *)malloc(0x10);
                {
                    size_t total = len + 1;
                    if (total < 8) {
                        if ((total & 4) == 0) {
                            if ((total != 0) && (*dst = *s, (total & 2) != 0)) {
                                *(uint16_t *)(dst + (size_t)(total - 2)) =
                                    *(uint16_t *)(s + (size_t)(total - 2));
                            }
                        } else {
                            *(uint32_t *)dst = *(uint32_t *)s;
                            *(uint32_t *)(dst + (size_t)(total - 4)) =
                                *(uint32_t *)(s + (size_t)(total - 4));
                        }
                    } else {
                        *(uint64_t *)(dst + (size_t)(total - 8)) =
                            *(uint64_t *)(s + (size_t)(total - 8));
                        if (7 < (size_t)(total - 1)) {
                            size_t i = 0;
                            size_t n;
                            do {
                                n = (size_t)i + 8;
                                *(uint64_t *)(dst + i) = *(uint64_t *)(s + i);
                                i = n;
                            } while (n < (size_t)(total - 1) & 0xfffffff8);
                        }
                    }
                }
                printf("Registrato: %s (%zu caratteri)\n", dst, len);
                ptr = ptr + 1;
                free(dst);
                if (ptr == end) {
                    return 0;
                }
            }
            ptr = ptr + 1;
            printf("Nome troppo lungo: %zu caratteri\n", len);
        } while (ptr != end);
    }
    return 0;
}
