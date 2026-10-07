#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    unsigned int n;
    unsigned int sum = 0;
    int *arr;
    int end;
    int v;
    int *p;

    if (argc > 1) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        n = (unsigned int)strtol(argv[1], NULL, 10);
        if (n < 0x65u) {
            arr = (int *)malloc((size_t)(n * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", n, (unsigned int)(n * 4 & 0xff));
            if (n != 0) {
                end = (int)n * 3;
                v = 1;
                p = arr;
                do {
                    *p = v;
                    sum = sum + (unsigned int)v;
                    v = v + 3;
                    p = p + 1;
                } while (v != end + 1);
            }
            printf("Somma: %u\n", sum);
            free(arr);
            return 0;
        }
        else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
