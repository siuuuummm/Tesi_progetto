#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**
 * Reconstructed from FUN_004005e0
 */
char *copy_string_to_buffer(char *param_1) {
    size_t sVar3 = strlen(param_1);
    char *pcVar4 = (char *)0;
    if (sVar3 < 0x11) {
        pcVar4 = (char *)malloc(0x10);
        uint64_t uVar1 = sVar3 + 1;
        uint32_t uVar2 = (uint32_t)uVar1;
        if (uVar2 < 8) {
            if ((uVar1 & 4) == 0) {
                if ((uVar2 != 0) && (*pcVar4 = *param_1, (uVar1 & 2) != 0)) {
                    *(uint16_t *)(pcVar4 + (uVar1 - 2)) = *(uint16_t *)(param_1 + (uVar1 - 2));
                }
            } else {
                *(uint32_t *)pcVar4 = *(uint32_t *)param_1;
                *(uint32_t *)(pcVar4 + (uVar1 - 4)) = *(uint32_t *)(param_1 + (uVar1 - 4));
            }
        } else {
            *(uint64_t *)(pcVar4 + (uVar1 - 8)) = *(uint64_t *)(param_1 + (uVar1 - 8));
            if (7 < uVar2 - 1) {
                uint32_t uVar5 = 0;
                do {
                    uint32_t uVar6 = uVar5 + 8;
                    *(uint64_t *)(pcVar4 + uVar5) = *(uint64_t *)(param_1 + uVar5);
                    uVar5 = uVar6;
                } while (uVar6 < (uVar2 - 1 & 0xfffffff8));
            }
        }
    }
    return pcVar4;
}

/**
 * Reconstructed from FUN_004003c0
 */
int main(int argc, char **argv) {
    setvbuf(stdout, (char *)0, 2, 0);
    if (1 < argc) {
        char **puVar6 = (char **)((uintptr_t)argv + 8);
        char **puVar1 = (char **)((uintptr_t)argv + 0x10 + (uintptr_t)(argc - 2) * 8);
        do {
            while (1) {
                char *__s = *puVar6;
                size_t sVar3 = strlen(__s);
                if (0x10 < sVar3) {
                    break;
                }
                char *__ptr = (char *)malloc(0x10);
                uint64_t uVar5 = sVar3 + 1;
                uint32_t uVar2 = (uint32_t)uVar5;
                if (uVar2 < 8) {
                    if ((uVar5 & 4) == 0) {
                        if ((uVar2 != 0) && (*__ptr = *__s, (uVar5 & 2) != 0)) {
                            *(uint16_t *)(__ptr + (uVar5 - 2)) = *(uint16_t *)(__s + (uVar5 - 2));
                        }
                    } else {
                        *(uint32_t *)__ptr = *(uint32_t *)__s;
                        *(uint32_t *)(__ptr + (uVar5 - 4)) = *(uint32_t *)(__s + (uVar5 - 4));
                    }
                } else {
                    *(uint64_t *)(__ptr + (uVar5 - 8)) = *(uint64_t *)(__s + (uVar5 - 8));
                    if (7 < uVar2 - 1) {
                        uint32_t uVar5_loop = 0;
                        do {
                            uint32_t uVar4 = uVar5_loop + 8;
                            *(uint64_t *)(__ptr + uVar5_loop) = *(uint64_t *)(__s + uVar5_loop);
                            uVar5_loop = uVar4;
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
