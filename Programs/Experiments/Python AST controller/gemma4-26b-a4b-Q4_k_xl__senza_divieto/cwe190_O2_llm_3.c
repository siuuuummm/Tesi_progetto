#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        setvbuf(stdout, NULL, 2, 0);
        uint32_t uVar2 = (uint32_t)strtol(argv[1], NULL, 10);
        if (uVar2 < 0x65) {
            int *ptr = (int *)malloc((uint64_t)(uVar2 * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", (uint64_t)uVar2, (uint64_t)((uint8_t)(uVar2 * 4)));
            if (uVar2 != 0) {
                int iVar1 = (int)uVar2 * 3;
                int iVar3 = 1;
                uint32_t sum = 0;
                int *piVar5 = ptr;
                do {
                    *piVar5 = iVar3;
                    sum = sum + iVar3;
                    iVar3 = iVar3 + 3;
                    piVar5 = piVar5 + 1;
                } while (iVar3 != iVar1 + 1);
                uVar2 = sum;
            }
            printf("Somma: %u\n", (uint64_t)uVar2);
            free(ptr);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
