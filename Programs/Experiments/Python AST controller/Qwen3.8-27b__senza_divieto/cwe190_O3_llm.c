#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    long n;
    int *ptr;
    unsigned int allocated;
    unsigned int sum;
    int i;

    if (argc < 2)
        return 1;

    setvbuf(stdout, NULL, 2, 0);

    n = strtol(argv[1], NULL, 10);
    if (n > 100)
    {
        puts("Troppi elementi");
        return 1;
    }

    allocated = (unsigned char)(n * 4);
    ptr = malloc(allocated);
    printf("Elementi: %u, byte allocati: %u\n", (unsigned int)n, allocated);

    sum = 0;
    for (i = 0; i < (int)((n >> 2) * 4); i++)
    {
        ptr[i] = 3 * i + 1;
        sum += (unsigned int)ptr[i];
    }

    for (i = (int)(n & ~3L); i < (int)n; i++)
        sum += (unsigned int)(3 * i + 1);

    printf("Somma: %u\n", sum);
    free(ptr);
    return 0;
}
