#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    int iVar1;
    unsigned int uVar2;
    int iVar3;
    int *__ptr;
    int uVar4;
    int *piVar5;

    if (1 < argc) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        uVar2 = (unsigned int)strtol(argv[1], 0, 10);
        if (uVar2 < 0x65) {
            __ptr = (int *)malloc((unsigned long)(uVar2 * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n",
                   (unsigned long)uVar2,
                   (unsigned long)(unsigned char)(uVar2 * 4));
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
            printf("Somma: %u\n", (unsigned long)uVar2);
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