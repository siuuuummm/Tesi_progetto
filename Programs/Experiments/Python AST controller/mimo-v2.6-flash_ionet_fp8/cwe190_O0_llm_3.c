#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    uint8_t bVar1;
    unsigned int uVar2;
    void *__ptr;
    unsigned int local_10;
    unsigned int local_c;

    if (argc < 2) {
        return 1;
    } else {
        setvbuf(stdout, (char *)0x0, 2, 0);
        uVar2 = atoi(argv[1]);
        if (uVar2 < 0x65) {
            bVar1 = (uint8_t)(uVar2 << 2);
            __ptr = malloc((unsigned long)bVar1);
            printf("Elementi: %u, byte allocati: %u\n", uVar2, bVar1);
            local_c = 0;
            for (local_10 = 0; local_10 < uVar2; local_10 = local_10 + 1) {
                *(unsigned int *)((long)__ptr + (unsigned long)local_10 * 4) = local_10 * 3 + 1;
                local_c = local_c + *(int *)((long)__ptr + (unsigned long)local_10 * 4);
            }
            printf("Somma: %u\n", local_c);
            free(__ptr);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
}