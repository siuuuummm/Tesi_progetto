#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv) {
    uint8_t bVar1;
    uint32_t uVar2;
    int uVar3;
    void *ptr;
    uint32_t local_10;
    uint32_t local_c;

    if (argc < 2) {
        uVar3 = 1;
    } else {
        setvbuf(stdout, NULL, 2, 0);
        uVar2 = (uint32_t)atoi(argv[1]);
        if (uVar2 < 0x65) {
            bVar1 = (uint8_t)(uVar2 << 2);
            ptr = malloc((size_t)bVar1);
            printf("Elementi: %u, byte allocati: %u\n", uVar2, (uint32_t)bVar1);
            local_c = 0;
            for (local_10 = 0; local_10 < uVar2; local_10++) {
                *(uint32_t *)((uintptr_t)ptr + (uintptr_t)local_10 * 4) = (uint32_t)(local_10 * 3 + 1);
                local_c += *(uint32_t *)((uintptr_t)ptr + (uintptr_t)local_10 * 4);
            }
            printf("Somma: %u\n", local_c);
            free(ptr);
            uVar3 = 0;
        } else {
            puts("Troppi elementi");
            uVar3 = 1;
        }
    }
    return uVar3;
}
