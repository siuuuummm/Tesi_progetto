#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    uint64_t uVar3;

    if (argc < 2) {
        uVar3 = 1;
    } else {
        setvbuf(stdout, (char *)0, 2, 0);
        uint32_t uVar2 = (uint32_t)atoi(argv[1]);
        if (uVar2 < 0x65) {
            uint8_t bVar1 = (uint8_t)(uVar2 << 2);
            void *__ptr = malloc((size_t)bVar1);
            printf("Elementi: %u, byte allocati: %u\n", (unsigned int)uVar2, (unsigned int)bVar1);
            uint32_t local_c = 0;
            for (uint32_t local_10 = 0; local_10 < uVar2; local_10++) {
                *((uint32_t *)((uintptr_t)__ptr + (uintptr_t)local_10 * 4)) = local_10 * 3 + 1;
                local_c = local_c + *((uint32_t *)((uintptr_t)__ptr + (uintptr_t)local_10 * 4));
            }
            printf("Somma: %u\n", (unsigned int)local_c);
            free(__ptr);
            uVar3 = 0;
        } else {
            puts("Troppi elementi");
            uVar3 = 1;
        }
    }
    return (int)uVar3;
}
