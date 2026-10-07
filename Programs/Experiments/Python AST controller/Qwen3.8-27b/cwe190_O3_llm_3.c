#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int a[4] = { 0, 1, 2, 3 };
int b[4] = { 1, 1, 1, 1 };
int c[4] = { 4, 4, 4, 4 };

int main(int argc, char *argv[])
{
    long long n64;
    unsigned n;
    int *buf;
    unsigned sum;
    long i;

    if (argc < 2) {
        return 1;
    }

    setvbuf(stdout, (char *)0, 2, 0);

    n64 = strtol(argv[1], 0, 10);
    n = (unsigned)n64;

    if (100 < n) {
        puts("Troppi elementi");
        return 1;
    }

    buf = (int *)malloc((unsigned long)(n * 4 & 0xff));
    printf("Elementi: %u, byte allocati: %u\n", n, (unsigned char)(n * 4));

    sum = 0;
    for (i = 0; i < (long)n; i++) {
        int k = (int)(i & 3);
        buf[i] = a[k] * 3 + b[k];
        a[k] += c[k];
        sum += (unsigned)buf[i];
    }

    printf("Somma: %u\n", (unsigned long)sum);
    free(buf);
    return 0;
}
