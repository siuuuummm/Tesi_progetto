#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    setvbuf(stdout, NULL, _IOLBF, 0);

    unsigned int n = (unsigned int)strtol(argv[1], NULL, 10);

    if (n > 100) {
        puts("Troppi elementi");
        return 1;
    }

    unsigned char alloc = n * 4;
    int *arr = (int *)malloc(alloc);

    printf("Elementi: %u, byte allocati: %u\n", n, alloc);

    unsigned int somma = 0;
    for (unsigned int i = 0; i < n; i++) {
        arr[i] = i * 3 + 1;
        somma += arr[i];
    }

    printf("Somma: %u\n", somma);
    free(arr);
    return 0;
}
