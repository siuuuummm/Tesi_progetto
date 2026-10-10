#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char **end_arg;
    char *s;
    uint32_t n32;
    size_t len;
    char *ptr;
    uint32_t i;
    uint64_t n64;
    char **cur_arg;

    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        cur_arg = (char **)(argv + 1);
        end_arg = (char **)((char *)argv + 0x10 + (uint64_t)(argc - 2) * 8);
        do {
            while (1) {
                s = *cur_arg;
                len = strlen(s);
                if (0x10 < len) break;
                ptr = (char *)malloc(0x10);
                n64 = len + 1;
                n32 = (uint32_t)n64;
                if (n32 < 8) {
                    if ((n64 & 4) == 0) {
                        if ((n32 != 0) && (*ptr = *s, (n64 & 2) != 0)) {
                            *(uint16_t *)(ptr + ((n64 & 0xffffffffffffffffULL) - 2)) =
                                *(uint16_t *)(s + ((n64 & 0xffffffffffffffffULL) - 2));
                        }
                    } else {
                        *(uint32_t *)ptr = *(uint32_t *)s;
                        *(uint32_t *)(ptr + ((n64 & 0xffffffffffffffffULL) - 4)) =
                            *(uint32_t *)(s + ((n64 & 0xffffffffffffffffULL) - 4));
                    }
                } else {
                    *(uint64_t *)(ptr + ((n64 & 0xffffffffffffffffULL) - 8)) =
                        *(uint64_t *)(s + ((n64 & 0xffffffffffffffffULL) - 8));
                    if (7 < n32 - 1) {
                        n64 = 0;
                        do {
                            i = (uint32_t)n64 + 8;
                            *(uint64_t *)(ptr + n64) = *(uint64_t *)(s + n64);
                            n64 = (uint64_t)i;
                        } while (i < (n32 - 1 & 0xfffffff8));
                    }
                }
                printf("Registrato: %s (%zu caratteri)\n", ptr, len);
                cur_arg = cur_arg + 1;
                free(ptr);
                if (cur_arg == end_arg) {
                    return 0;
                }
            }
            cur_arg = cur_arg + 1;
            printf("Nome troppo lungo: %zu caratteri\n", len);
        } while (cur_arg != end_arg);
    }
    return 0;
}
