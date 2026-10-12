#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned int n;
    long parsed;
    unsigned int sum;
    unsigned int v[4];
    const unsigned int c[4] = {1, 1, 1, 1};
    const unsigned int st[4] = {4, 4, 4, 4};
    int *ptr;
    unsigned int i;
    unsigned int k;
    unsigned int o[4];

    if (argc < 2) {
        return 1;
    }
    setvbuf(stdout, NULL, _IONBF, 0);
    parsed = strtol(argv[1], NULL, 10);
    n = (unsigned int)parsed;
    if (n > 100) {
        puts("Troppi elementi");
        return 1;
    }
    ptr = (int *)malloc((size_t)(uint8_t)(n * 4));
    printf("Elementi: %u, byte allocati: %u\n", n, (unsigned int)(uint8_t)(n * 4));

    for (k = 0; k < 4; k++) {
        v[k] = (unsigned int)k;
    }
    for (i = 0; i < n / 4; i++) {
        for (k = 0; k < 4; k++) {
            o[k] = 3 * v[k] + c[k];
            v[k] = v[k] + st[k];
        }
        for (k = 0; k < 4; k++) {
            ptr[i * 4 + k] = (int)o[k];
        }
    }

    sum = 0;
    for (i = 0; i < n; i++) {
        sum = sum + 3 * (unsigned int)i + 1;
    }

    printf("Somma: %u\n", sum);
    free(ptr);
    return 0;
}