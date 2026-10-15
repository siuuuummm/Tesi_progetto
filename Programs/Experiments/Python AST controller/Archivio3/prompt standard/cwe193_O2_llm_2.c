#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    uint32_t uVar2;
    uint32_t uVar4;
    uint64_t uVar5;
    size_t len;

    setvbuf(stdout, (char *)0, 2, 0);

    if (1 < argc) {
        char **s = (char **)(argv + 1);
        char **s_end = (char **)(argv + argc);
        do {
            while (1) {
                char *src = *s;
                len = strlen(src);
                if (0x10 < len)
                    break;
                char *dst = (char *)malloc(0x10);
                uVar2 = (uint32_t)(len + 1);
                if (uVar2 < 8) {
                    if ((len + 1 & 4) == 0) {
                        if (uVar2 != 0) {
                            *dst = *src;
                            if ((len + 1 & 2) != 0) {
                                *(uint16_t *)(dst + (len + 1 - 2)) =
                                    *(uint16_t *)(src + (len + 1 - 2));
                            }
                        }
                    }
                    else {
                        *(uint32_t *)dst = *(uint32_t *)src;
                        *(uint32_t *)(dst + (len + 1 - 4)) =
                            *(uint32_t *)(src + (len + 1 - 4));
                    }
                }
                else {
                    *(uint64_t *)(dst + (len + 1 - 8)) =
                        *(uint64_t *)(src + (len + 1 - 8));
                    if (7 < uVar2 - 1) {
                        uVar5 = 0;
                        do {
                            uVar4 = (int)uVar5 + 8;
                            *(uint64_t *)(dst + uVar5) = *(uint64_t *)(src + uVar5);
                            uVar5 = (uint64_t)uVar4;
                        } while (uVar4 < (uVar2 - 1 & 0xfffffff8));
                    }
                }
                printf("Registrato: %s (%zu caratteri)\n", dst, len);
                s = s + 1;
                free(dst);
                if (s == s_end)
                    return 0;
            }
            s = s + 1;
            printf("Nome troppo lungo: %zu caratteri\n", len);
        } while (s != s_end);
    }
    return 0;
}
