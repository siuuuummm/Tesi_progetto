#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Function reconstructed from FUN_004005e0
char *duplicate_string_16(char *param_1) {
    uint64_t uVar1;
    uint32_t uVar2;
    size_t sVar3;
    char *pcVar4;
    uint32_t uVar5;
    uint32_t uVar6;

    sVar3 = strlen(param_1);
    pcVar4 = (char *)0x0;
    if (sVar3 < 0x11) {
        pcVar4 = (char *)malloc(0x10);
        uVar1 = sVar3 + 1;
        uVar2 = (uint32_t)uVar1;
        if (uVar2 < 8) {
            if ((uVar1 & 4) == 0) {
                if ((uVar2 != 0) && (*pcVar4 = *param_1, (uVar1 & 2) != 0)) {
                    *(uint16_t *)(pcVar4 + ((uVar1 & 0xffffffff) - 2)) =
                        *(uint16_t *)(param_1 + ((uVar1 & 0xffffffff) - 2));
                }
            } else {
                *(uint32_t *)pcVar4 = *(uint32_t *)param_1;
                *(uint32_t *)(pcVar4 + ((uVar1 & 0xffffffff) - 4)) =
                    *(uint32_t *)(param_1 + ((uVar1 & 0xffffffff) - 4));
            }
        } else {
            *(uint64_t *)(pcVar4 + ((uVar1 & 0xffffffff) - 8)) =
                *(uint64_t *)(param_1 + ((uVar1 & 0xffffffff) - 8));
            if (7 < (uint32_t)uVar2 - 1) {
                uVar5 = 0;
                do {
                    uVar6 = uVar5 + 8;
                    *(uint64_t *)(pcVar4 + uVar5) = *(uint64_t *)(param_1 + uVar5);
                    uVar5 = uVar6;
                } while (uVar6 < (uint32_t)(uVar2 - 1 & 0xfffffff8));
            }
        }
    }
    return pcVar4;
}

int main(int argc, char **argv) {
    char **puVar6;
    char **puVar1;
    char *__s;
    size_t sVar3;
    char *__ptr;
    uint32_t uVar2;
    uint32_t uVar4;
    uint64_t uVar5;

    setvbuf(stdout, NULL, 2, 0);

    if (argc > 1) {
        puVar6 = (char **)(argv + 1);
        puVar1 = (char **)(argv + 2 + (argc - 2));

        do {
            while (1) {
                __s = *puVar6;
                sVar3 = strlen(__s);
                if (sVar3 > 0x10) {
                    break;
                }
                __ptr = (char *)malloc(0x10);
                uVar5 = sVar3 + 1;
                uVar2 = (uint32_t)uVar5;

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
                    if (7 < (uint32_t)uVar2 - 1) {
                        uVar5 = 0;
                        do {
                            uVar4 = (uint32_t)uVar5 + 8;
                            *(uint64_t *)(__ptr + uVar5) = *(uint64_t *)(__s + uVar5);
                            uVar5 = uVar4;
                        } while (uVar4 < (uint32_t)(uVar2 - 1 & 0xfffffff8));
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
