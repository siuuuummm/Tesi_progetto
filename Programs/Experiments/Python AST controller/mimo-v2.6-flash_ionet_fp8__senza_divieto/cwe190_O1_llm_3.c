#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int param_1, char **param_2)
{
    uint32_t uVar1;
    int iVar2;
    int *ptr;
    int ret;
    int iVar4;
    int *piVar5;

    if (1 < param_1) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        uVar1 = (uint32_t)strtol(param_2[1], (char **)0x0, 10);
        if (uVar1 < 0x65) {
            ptr = (int *)malloc((size_t)(uVar1 * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", uVar1, uVar1 * 4 & 0xff);
            if (uVar1 != 0) {
                iVar4 = uVar1 * 3;
                iVar2 = 1;
                uVar1 = 0;
                piVar5 = ptr;
                do {
                    *piVar5 = iVar2;
                    uVar1 = uVar1 + iVar2;
                    iVar2 = iVar2 + 3;
                    piVar5 = piVar5 + 1;
                } while (iVar2 != iVar4 + 1);
            }
            printf("Somma: %u\n", uVar1);
            free(ptr);
            ret = 0;
        }
        else {
            puts("Troppi elementi");
            ret = 1;
        }
        return ret;
    }
    return 1;
}