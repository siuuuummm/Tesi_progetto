#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc > 1) {
        setvbuf(stdout, NULL, 2, 0);
        uint32_t n = (uint32_t)strtol(argv[1], NULL, 10);
        if (n < 0x65) {
            int *ptr = (int *)malloc((uint32_t)(n * 4) & 0xffu);
            printf("Elementi: %u, byte allocati: %u\n", (uint32_t)n,
                   (uint32_t)(uint8_t)(n * 4u));
            uint32_t sum = 0;
            if (n != 0) {
                int limit = (int)(n * 3);
                int value = 1;
                int *p = ptr;
                do {
                    *p = value;
                    sum = sum + (uint32_t)value;
                    value = value + 3;
                    p = p + 1;
                } while (value != limit + 1);
            }
            printf("Somma: %u\n", (uint32_t)sum);
            free(ptr);
            return 0;
        }
        else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
