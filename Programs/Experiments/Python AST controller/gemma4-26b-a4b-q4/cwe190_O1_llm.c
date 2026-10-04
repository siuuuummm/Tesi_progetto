#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        setvbuf(stdout, (char *)0, 2, 0);
        uint32_t uVar1 = (uint32_t)strtol(argv[1], NULL, 10);
        if (uVar1 < 0x65) {
            int *__ptr = (int *)malloc((size_t)(uVar1 * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", (unsigned int)uVar1, (unsigned int)(uVar1 * 4 & 0xff));
            if (uVar1 != 0) {
                int iVar4 = uVar1 * 3;
                int iVar2 = 1;
                uVar1 = 0;
                int *piVar5 = __ptr;
                do {
                    *piVar5 = iVar2;
                    uVar1 = uVar1 + iVar2;
                    iVar2 = iVar2 + 3;
                    piVar5 = piVar5 + 1;
                } while (iVar2 != iVar4 + 1);
            }
            printf("Somma: %u\n", (unsigned int)uVar1);
            free(__ptr);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
