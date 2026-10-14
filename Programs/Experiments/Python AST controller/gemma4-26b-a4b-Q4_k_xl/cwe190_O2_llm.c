#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        setvbuf(stdout, NULL, 2, 0);
        uint32_t uVar2 = (uint32_t)strtol(argv[1], NULL, 10);
        if (uVar2 < 0x65) {
            int *__ptr = (int *)malloc((size_t)(uVar2 * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", (unsigned int)uVar2, (unsigned int)((uint8_t)(uVar2 * 4)));
            if (uVar2 != 0) {
                int iVar1 = uVar2 * 3;
                int iVar3 = 1;
                uVar2 = 0;
                int *piVar5 = __ptr;
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
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
