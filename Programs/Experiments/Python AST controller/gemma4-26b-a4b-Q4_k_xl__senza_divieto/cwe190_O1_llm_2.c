#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    uint32_t uVar1;
    int iVar2;
    int *__ptr;
    uint64_t uVar3;
    int iVar4;
    int *piVar5;

    if (argc > 1) {
        setvbuf(stdout, NULL, 2, 0);
        uVar1 = (uint32_t)strtol(argv[1], NULL, 10);
        if (uVar1 < 0x65) {
            __ptr = (int *)malloc((uint64_t)(uVar1 * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", (unsigned int)uVar1, (unsigned int)(uVar1 * 4 & 0xff));
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
            printf("Somma: %u\n", (unsigned int)uVar1);
            free(__ptr);
            uVar3 = 0;
        } else {
            puts("Troppi elementi");
            uVar3 = 1;
        }
        return (int)uVar3;
    }
    return 1;
}
