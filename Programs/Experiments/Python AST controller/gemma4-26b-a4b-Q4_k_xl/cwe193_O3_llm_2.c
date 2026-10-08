#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv) {
    setvbuf(stdout, NULL, 2, 0);
    if (argc > 1) {
        char **puVar6 = argv + 1;
        char **puVar1 = argv + 2 + (argc - 2);

        do {
            char *s_ptr;
            size_t sVar3;
            char *__ptr;
            uint32_t uVar2;
            uint64_t uVar5;
            uint32_t uVar4;

            s_ptr = *puVar6;
            sVar3 = strlen(s_ptr);

            if (sVar3 <= 16) {
                __ptr = (char *)malloc(0x10);
                uVar5 = (uint64_t)sVar3 + 1;
                uVar2 = (uint32_t)uVar5;

                if (uVar2 < 8) {
                    if ((uVar5 & 4) == 0) {
                        if ((uVar2 != 0) && (*__ptr = *s_ptr, (uVar5 & 2) != 0)) {
                            *(uint16_t *)(__ptr + (uVar5 - 2)) = *(uint16_t *)(s_ptr + (uVar5 - 2));
                        }
                    } else {
                        *(uint32_t *)__ptr = *(uint32_t *)s_ptr;
                        *(uint32_t *)(__ptr + (uVar5 - 4)) = *(uint32_t *)(s_ptr + (uVar5 - 4));
                    }
                } else {
                    *(uint64_t *)(__ptr + (uVar5 - 8)) = *(uint64_t *)(s_ptr + (uVar5 - 8));
                    if (7 < (uint32_t)uVar2 - 1) {
                        uVar5 = 0;
                        do {
                            uVar4 = (uint32_t)uVar5 + 8;
                            *(uint64_t *)(__ptr + uVar5) = *(uint64_t *)(s_ptr + uVar5);
                            uVar5 = (uint64_t)uVar4;
                        } while (uVar4 < ((uint32_t)uVar2 - 1 & 0xfffffff8));
                    }
                }
                printf("Registrato: %s (%zu caratteri)\n", __ptr, sVar3);
                puVar6++;
                free(__ptr);
                if (puVar6 == puVar1) {
                    return 0;
                }
            } else {
                puVar6++;
                printf("Nome troppo lungo: %zu caratteri\n", sVar3);
            }
        } while (puVar6 != puVar1);
    }
    return 0;
}
