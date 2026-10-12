#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char **argv)
{
    uint8_t alloc_bytes;
    unsigned int sum;
    unsigned int i;
    unsigned int count;
    void *ptr;

    if (argc < 2) {
        return 1;
    } else {
        setvbuf(stdout, (char *)0x0, 2, 0);
        count = (unsigned int)atoi(argv[1]);
        if (count < 0x65) {
            alloc_bytes = (uint8_t)(count << 2);
            ptr = malloc((size_t)alloc_bytes);
            printf("Elementi: %u, byte allocati: %u\n", count,
                   alloc_bytes);
            sum = 0;
            for (i = 0; i < count; i = i + 1) {
                *(unsigned int *)((long)ptr + (long)i * 4) = i * 3 + 1;
                sum = sum + *(int *)((long)ptr + (long)i * 4);
            }
            printf("Somma: %u\n", sum);
            free(ptr);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
}