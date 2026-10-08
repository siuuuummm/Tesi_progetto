#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    setvbuf(stdout, (char *)0, 2, 0);

    unsigned int n = strtol(argv[1], 0, 10);

    if (n > 100) {
        puts("Troppi elementi");
        return 1;
    }

    unsigned char byte_allocati = n * 4;
    int *arr = malloc(byte_allocati);

    printf("Elementi: %u, byte allocati: %u\n", n, byte_allocati);

    unsigned int somma = 0;
    int i = 0;
    while (i < n) {
        arr[i] = 3 * i + 1;
        somma += arr[i];
        i = i + 1;
    }

    printf("Somma: %u\n", somma);

    free(arr);

    return 0;
}
