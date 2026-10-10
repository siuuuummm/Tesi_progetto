#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    void *ptr;
    unsigned int n;
    unsigned char alloc_bytes;
    unsigned int i;
    unsigned int sum;

    if (argc < 2) {
        return 1;
    }

    setvbuf(stdout, NULL, 2, 0);
    n = (unsigned int)atoi(argv[1]);

    if (n < 0x65) {
        alloc_bytes = (unsigned char)(n << 2);
        ptr = malloc((size_t)alloc_bytes);
        printf("Elementi: %u, byte allocati: %u\n", n, (unsigned int)alloc_bytes);
        sum = 0;
        for (i = 0; i < n; i = i + 1) {
            ((unsigned int *)ptr)[i] = i * 3 + 1;
            sum = sum + ((int *)ptr)[i];
        }
        printf("Somma: %u\n", sum);
        free(ptr);
        return 0;
    }

    puts("Troppi elementi");
    return 1;
}
