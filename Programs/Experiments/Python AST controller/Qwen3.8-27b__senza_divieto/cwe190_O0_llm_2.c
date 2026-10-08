#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }
    setvbuf(stdout, NULL, _IONBF, 0);
    unsigned int n = atoi(argv[1]);
    if (n > 100) {
        puts("Troppi elementi");
        return 1;
    }
    unsigned char size = n * sizeof(int);
    unsigned int *buf = malloc(size);
    printf("Elementi: %u, byte allocati: %u\n", n, size);
    unsigned int sum = 0;
    unsigned int i;
    for (i = 0; i < n; i++) {
        buf[i] = i * 3 + 1;
        sum += buf[i];
    }
    printf("Somma: %u\n", sum);
    free(buf);
    return 0;
}
