#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    uint8_t bVar1;
    uint32_t uVar2;
    void *__ptr;
    uint32_t local_10;
    uint32_t local_c;

    if (argc < 2) {
        return 1;
    }
    else {
        setvbuf(stdout, (char *)0, 2, 0);
        uVar2 = (uint32_t)atoi(*(char **)(argv + 1));
        if (uVar2 < 0x65) {
            bVar1 = (uint8_t)(uVar2 << 2);
            __ptr = malloc((size_t)bVar1);
            printf("Elementi: %u, byte allocati: %u\n", (unsigned int)uVar2, (unsigned int)bVar1);
            local_c = 0;
            for (local_10 = 0; local_10 < uVar2; local_10 = local_10 + 1) {
                *(uint32_t *)((char *)__ptr + (size_t)local_10 * 4) = local_10 * 3 + 1;
                local_c = local_c + *(int32_t *)((char *)__ptr + (size_t)local_10 * 4);
            }
            printf("Somma: %u\n", (unsigned int)local_c);
            free(__ptr);
            return 0;
        }
        else {
            puts("Troppi elementi");
            return 1;
        }
    }
}
