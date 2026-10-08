#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    uint32_t n;
    void *ptr;
    uint32_t i;
    uint32_t sum;

    if (argc < 2) {
        return 1;
    }

    setvbuf(stdout, (char *)0x0, 2, 0);
    n = (uint32_t)atoi(*(char **)(argv + 1));
    if (n < 0x65) {
        uint8_t nbytes = (uint8_t)(n << 2);
        ptr = malloc((size_t)nbytes);
        printf("Elementi: %u, byte allocati: %u\n", (unsigned)n, (unsigned)nbytes);
        sum = 0;
        for (i = 0; i < n; i = i + 1) {
            *(uint32_t *)((long)ptr + (unsigned long)i * 4) = i * 3 + 1;
            sum = sum + *(uint32_t *)((long)ptr + (unsigned long)i * 4);
        }
        printf("Somma: %u\n", (unsigned)sum);
        free(ptr);
        return 0;
    }
    else {
        puts("Troppi elementi");
        return 1;
    }
}
