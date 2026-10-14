#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv) {
    uint32_t uVar1;
    int32_t iVar2;
    int32_t *__ptr;
    int32_t iVar4;
    int32_t *piVar5;

    if (argc > 1) {
        setvbuf(stdout, (char *)0, 2, 0);
        uVar1 = (uint32_t)strtol(argv[1], NULL, 10);
        if (uVar1 < 0x65) {
            __ptr = (int32_t *)malloc((uint64_t)(uVar1 * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", uVar1, (unsigned int)(uVar1 * 4 & 0xff));
            if (uVar1 != 0) {
                iVar4 = uVar1 * 3;
                iVar2 = 1;
                uVar1 = 0;
                piVar5 = __ptr;
                do {
                    *piVar5 = iVar2;
                    uVar1 = uVar1 + iVar2;
                    iVar2 = iVar2 + 3;
                    piVar5 = piVar5 + 1;
                } while (iVar2 != iVar4 + 1);
            }
            printf("Somma: %u\n", uVar1);
            free(__ptr);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
