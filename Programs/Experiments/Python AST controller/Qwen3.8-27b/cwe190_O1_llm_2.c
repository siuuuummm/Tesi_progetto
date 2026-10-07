#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    unsigned int n;
    unsigned int sum;
    int *buf;

    if (argc > 1) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        n = (unsigned int)strtol(argv[1], NULL, 10);
        if (n < 0x65) {
            buf = (int *)malloc((unsigned long)(n * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", n, (unsigned int)(n * 4 & 0xff));
            if (n != 0) {
                int stop = (int)(n * 3);
                int val = 1;
                sum = 0;
                int *p = buf;
                do {
                    *p = val;
                    sum = sum + val;
                    val = val + 3;
                    p = p + 1;
                } while (val != stop + 1);
            }
            printf("Somma: %u\n", sum);
            free(buf);
            return 0;
        }
        else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
