#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv) {
    setvbuf(stdout, NULL, 2, 0);
    if (argc > 1) {
        char **puVar6 = &argv[1];
        char **puVar1 = (char **)((uintptr_t)argv + 0x10 + (uintptr_t)(argc - 2) * 8);
        size_t sVar3 = 0;

        do {
            while (1) {
                char *__s = *puVar6;
                sVar3 = strlen(__s);
                if (0x10 < sVar3) {
                    break;
                }
                char *__ptr = (char *)malloc(0x10);
                uint64_t uVar5 = sVar3 + 1;
                uint32_t uVar2 = (uint32_t)uVar5;

                if (uVar2 < 8) {
                    if ((uVar5 & 4) == 0) {
                        if ((uVar2 != 0) && (*__ptr = *__s, (uVar5 & 2) != 0)) {
                            *(uint16_t *)(__ptr + ((uVar5 & 0xffffffff) - 2)) =
                                *(uint16_t *)(__s + ((uVar5 & 0xffffffff) - 2));
                        }
                    } else {
                        *(uint32_t *)__ptr = *(uint32_t *)__s;
                        *(uint32_t *)(__ptr + ((uVar5 & 0xffffffff) - 4)) =
                            *(uint32_t *)(__s + ((uVar5 & 0xffffffff) - 4));
                    }
                } else {
                    *(uint64_t *)(__ptr + ((uVar5 & 0xffffffff) - 8)) =
                        *(uint64_t *)(__s + ((uVar5 & 0xffffffff) - 8));
                    if (7 < uVar2 - 1) {
                        uVar5 = 0;
                        do {
                            uint64_t uVar4 = uVar5 + 8;
                            *(uint64_t *)(__ptr + uVar5) = *(uint64_t *)(__s + uVar5);
                            uVar5 = uVar4;
                        } while (uVar4 < (uVar2 - 1 & 0xfffffff8));
                    }
                }
                printf("Registrato: %s (%zu caratteri)\n", __ptr, sVar3);
                puVar6++;
                free(__ptr);
                if (puVar6 == puVar1) {
                    return 0;
                }
            }
            puVar6++;
            printf("Nome troppo lungo: %zu caratteri\n", sVar3);
        } while (puVar6 != puVar1);
    }
    return 0;
}
