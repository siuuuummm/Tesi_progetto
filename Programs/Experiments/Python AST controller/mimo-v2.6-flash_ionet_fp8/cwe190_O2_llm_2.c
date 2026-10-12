#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char **argv)
{
    int iVar1;
    uint32_t uVar2;
    int iVar3;
    int *__ptr;
    uint64_t uVar4;
    int *piVar5;

    if (1 < argc) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        uVar2 = (uint32_t)strtol(argv[1], 0, 10);
        if (uVar2 < 0x65) {
            __ptr = (int *)malloc((uint64_t)(uVar2 * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n",
                   (uint64_t)uVar2, (uint64_t)(uint8_t)(uVar2 * 4));
            if (uVar2 != 0) {
                iVar1 = uVar2 * 3;
                iVar3 = 1;
                uVar2 = 0;
                piVar5 = __ptr;
                do {
                    *piVar5 = iVar3;
                    uVar2 = uVar2 + iVar3;
                    iVar3 = iVar3 + 3;
                    piVar5 = piVar5 + 1;
                } while (iVar3 != iVar1 + 1);
            }
            printf("Somma: %u\n", (uint64_t)uVar2);
            free(__ptr);
            uVar4 = 0;
        }
        else {
            puts("Troppi elementi");
            uVar4 = 1;
        }
        return uVar4;
    }
    return 1;
}