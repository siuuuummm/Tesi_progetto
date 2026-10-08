#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, 2, 0);
    if (argc > 1) {
        char **puVar6 = (char **)(argv + 1);
        char **puVar1 = (char **)(argv + 2 + (argc - 2));

        do {
            while (1) {
                char *__s = *puVar6;
                size_t sVar3 = strlen(__s);
                if (sVar3 > 16) {
                    break;
                }
                char *__ptr = (char *)malloc(16);
                uint64_t uVar5 = sVar3 + 1;
                uint32_t uVar2 = (uint32_t)uVar5;

                if (uVar2 < 8) {
                    if ((uVar5 & 4) == 0) {
                        if (uVar2 != 0) {
                            *__ptr = *__s;
                            if ((uVar5 & 2) != 0) {
                                *(uint16_t *)(__ptr + (uVar5 - 2)) = *(uint16_t *)(__s + (uVar5 - 2));
                            }
                        }
                    } else {
                        *(uint32_t *)__ptr = *(uint32_t *)__s;
                        *(uint32_t *)(__ptr + (uVar5 - 4)) = *(uint32_t *)(__s + (uVar5 - 4));
                    }
                } else {
                    *(uint64_t *)(__ptr + (uVar5 - 8)) = *(uint64_t *)(__s + (uVar5 - 8));
                    if (uVar2 - 1 > 7) {
                        uint64_t uVar5_loop = 0;
                        while (1) {
                            uint64_t uVar4 = uVar5_loop + 8;
                            *(uint64_t *)(__ptr + uVar5_loop) = *(uint64_t *)(__s + uVar5_loop);
                            uVar5_loop = uVar4;
                            if (uVar4 >= (uVar2 - 1 & 0xfffffff8)) {
                                break;
                            }
                        }
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
