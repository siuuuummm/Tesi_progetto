#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    unsigned int n;
    int *ptr;
    int limit;
    int i;
    unsigned int sum;
    int *cursor;

    if (1 < argc) {
        setvbuf(stdout, NULL, _IONBF, 0);
        n = (unsigned int)strtol(argv[1], NULL, 10);
        if (n < 0x65) {
            ptr = (int *)malloc((n * 4) & 0xff);
            printf("Elementi: %u, byte allocati: %u\n", n, (uint8_t)(n * 4));
            if (n != 0) {
                limit = n * 3;
                i = 1;
                sum = 0;
                cursor = ptr;
                do {
                    *cursor = i;
                    sum = sum + i;
                    i = i + 3;
                    cursor = cursor + 1;
                } while (i != limit + 1);
            }
            printf("Somma: %u\n", sum);
            free(ptr);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
