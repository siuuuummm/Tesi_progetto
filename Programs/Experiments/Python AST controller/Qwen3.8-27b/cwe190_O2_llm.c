#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        setvbuf(stdout, NULL, 2, 0);
        unsigned n = (unsigned)strtol(argv[1], NULL, 10);
        if (n < 0x65) {
            int *arr = (int *)malloc((n * 4) & 0xff);
            printf("Elementi: %u, byte allocati: %u\n", n, (unsigned char)(n * 4));
            if (n != 0) {
                unsigned sum = 0;
                int i = 1;
                int idx = 0;
                do {
                    arr[idx++] = i;
                    sum += (unsigned)i;
                    i += 3;
                } while (i != (int)n * 3 + 1);
                printf("Somma: %u\n", sum);
            }
            free(arr);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
