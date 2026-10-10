#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    unsigned int n;
    unsigned int sum;
    int limit;
    int value;
    int *ptr;
    int *p;
    unsigned int ret;

    if (argc <= 1) {
        return 1;
    }
    setvbuf(stdout, (char *)0x0, 2, 0);
    n = (unsigned int)strtol(argv[1], (char **)0x0, 10);
    if (n < 0x65) {
        ptr = (int *)malloc((unsigned long)(unsigned char)(n * 4));
        printf("Elementi: %u, byte allocati: %u\n",
               n, (unsigned int)(unsigned char)(n * 4));
        sum = n;
        if (n != 0) {
            limit = n * 3;
            value = 1;
            sum = 0;
            p = ptr;
            do {
                *p = value;
                sum = sum + value;
                value = value + 3;
                p = p + 1;
            } while (value != limit + 1);
        }
        printf("Somma: %u\n", sum);
        free(ptr);
        ret = 0;
    } else {
        puts("Troppi elementi");
        ret = 1;
    }
    return ret;
}
