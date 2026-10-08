#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    uint32_t n;
    int *ptr;
    int *p;
    uint32_t sum;
    int val;
    int last;

    if (1 < argc) {
        setvbuf(stdout, (char *)0, 2, 0);
        n = (uint32_t)strtol(argv[1], 0, 10);
        if (n < 0x65) {
            ptr = (int *)malloc((uint32_t)((n * 4) & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", (unsigned int)n,
                   (unsigned int)((n * 4) & 0xff));
            if (n != 0) {
                last = (int)n * 3;
                val = 1;
                sum = 0;
                p = ptr;
                do {
                    *p = val;
                    sum = sum + (uint32_t)val;
                    val = val + 3;
                    p = p + 1;
                } while (val != last + 1);
            } else {
                sum = 0;
            }
            printf("Somma: %u\n", (unsigned int)sum);
            free(ptr);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
