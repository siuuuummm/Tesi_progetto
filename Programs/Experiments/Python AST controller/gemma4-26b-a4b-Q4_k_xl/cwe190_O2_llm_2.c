#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    int iVar1;
    uint32_t uVar2;
    int iVar3;
    int *ptr;
    uint64_t uVar4;
    int *piVar5;

    if (argc > 1) {
        setvbuf(stdout, NULL, 2, 0);
        uVar2 = (uint32_t)strtol(argv[1], NULL, 10);
        if (uVar2 < 0x65) {
            ptr = (int *)malloc((size_t)(uVar2 * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", (unsigned int)uVar2, (unsigned int)((uint8_t)(uVar2 * 4)));
            if (uVar2 != 0) {
                iVar1 = uVar2 * 3;
                iVar3 = 1;
                uVar2 = 0;
                piVar5 = ptr;
                do {
                    *piVar5 = iVar3;
                    uVar2 = uVar2 + iVar3;
                    iVar3 = iVar3 + 3;
                    piVar5 = piVar5 + 1;
                } while (iVar3 != iVar1 + 1);
            }
            printf("Somma: %u\n", (unsigned int)uVar2);
            free(ptr);
            uVar4 = 0;
        } else {
            puts("Troppi elementi");
            uVar4 = 1;
        }
        return (int)uVar4;
    }
    return 1;
}
