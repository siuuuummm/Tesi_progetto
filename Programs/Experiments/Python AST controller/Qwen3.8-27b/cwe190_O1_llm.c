#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (1 < argc) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        unsigned int n = (unsigned int)strtol(argv[1], (char **)0x0, 10);
        if (n < 0x65) {
            int *array = (int *)malloc(((n * 4) & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", n, (n * 4) & 0xff);
            if (n != 0) {
                unsigned int sum = 0;
                unsigned int value = 1;
                int *ptr = array;
                do {
                    *ptr = (int)value;
                    sum = sum + value;
                    value = value + 3;
                    ptr = ptr + 1;
                } while (value != (unsigned int)(n * 3 + 1));
            } else {
                sum = 0;
            }
            printf("Somma: %u\n", sum);
            free(array);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
