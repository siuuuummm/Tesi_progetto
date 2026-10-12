#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* main (FUN_004003d0) */
int main(int argc, long argv)
{
    int iVar1;
    uint32_t uVar2;
    int iVar3;
    int *__ptr;
    int *piVar5;

    if (1 < argc) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        uVar2 = (uint32_t)strtol(*(char **)(argv + 8), (char **)0x0, 10);
        if (uVar2 < 0x65) {
            __ptr = (int *)malloc((size_t)(uVar2 * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n",
                   (unsigned int)uVar2,
                   (unsigned int)(uint8_t)(uVar2 * 4));
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
            printf("Somma: %u\n", (unsigned int)uVar2);
            free(__ptr);
            return 0;
        }
        else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}