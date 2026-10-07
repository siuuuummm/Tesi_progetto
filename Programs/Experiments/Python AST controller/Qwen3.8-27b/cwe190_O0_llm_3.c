#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned int n;
    unsigned char alloc_bytes;
    unsigned int sum;
    unsigned int i;
    void *ptr;

    if (argc < 2) {
        return 1;
    }
    else {
        setvbuf(stdout, (char *)0x0, 2, 0);
        n = atoi(*(char **)((char *)argv + 8));
        if (n < 0x65) {
            alloc_bytes = (unsigned char)(n << 2);
            ptr = malloc((unsigned long)alloc_bytes);
            printf("Elementi: %u, byte allocati: %u\n", n, (unsigned int)alloc_bytes);
            sum = 0;
            for (i = 0; i < n; i = i + 1) {
                *(unsigned int *)((long)ptr + (unsigned long)i * 4) = i * 3 + 1;
                sum = sum + *(int *)((long)ptr + (unsigned long)i * 4);
            }
            printf("Somma: %u\n", sum);
            free(ptr);
            return 0;
        }
        else {
            puts("Troppi elementi");
            return 1;
        }
    }
}
