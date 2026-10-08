#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    uint32_t n;
    int bound;
    int value;
    int *buf;
    int *p;
    int ret;

    if (1 < argc) {
        setvbuf(stdout, NULL, 2, 0);
        n = (uint32_t)strtol(argv[1], NULL, 10);
        if (n < 0x65) {
            buf = (int *)malloc((unsigned long)(n * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", n, n * 4 & 0xff);
            if (n != 0) {
                bound = n * 3;
                value = 1;
                n = 0;
                p = buf;
                do {
                    *p = value;
                    n = n + value;
                    value = value + 3;
                    p = p + 1;
                } while (value != bound + 1);
            }
            printf("Somma: %u\n", n);
            free(buf);
            ret = 0;
        }
        else {
            puts("Troppi elementi");
            ret = 1;
        }
        return ret;
    }
    return 1;
}