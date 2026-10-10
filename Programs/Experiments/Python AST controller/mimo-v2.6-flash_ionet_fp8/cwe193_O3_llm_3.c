#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char **argp;
    char *src;
    size_t len;
    char *dst;
    uint32_t uVar2;
    uint64_t uVar5;
    uint32_t uVar4;
    char **end;

    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        argp = argv + 1;
        end = (char **)((char *)argv + 0x10 + (uint64_t)(argc - 2) * 8);
        do {
            while (true) {
                src = *argp;
                len = strlen(src);
                if (0x10 < len) break;
                dst = (char *)malloc(0x10);
                uVar5 = len + 1;
                uVar2 = (uint32_t)uVar5;
                if (uVar2 < 8) {
                    if ((uVar5 & 4) == 0) {
                        if ((uVar2 != 0) && (*dst = *src, (uVar5 & 2) != 0)) {
                            *(uint16_t *)(dst + ((uVar5 & 0xffffffff) - 2)) =
                                *(uint16_t *)(src + ((uVar5 & 0xffffffff) - 2));
                        }
                    }
                    else {
                        *(uint32_t *)dst = *(uint32_t *)src;
                        *(uint32_t *)(dst + ((uVar5 & 0xffffffff) - 4)) =
                            *(uint32_t *)(src + ((uVar5 & 0xffffffff) - 4));
                    }
                }
                else {
                    *(uint64_t *)(dst + ((uVar5 & 0xffffffff) - 8)) =
                        *(uint64_t *)(src + ((uVar5 & 0xffffffff) - 8));
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
                argp = argp + 1;
                free(dst);
                if (argp == end) {
                    return 0;
                }
            }
            argp = argp + 1;
            printf("Nome troppo lungo: %zu caratteri\n", len);
        } while (argp != end);
    }
    return 0;
}
