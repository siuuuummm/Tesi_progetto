#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char **argv)
{
    uint32_t n;
    int loop_end;
    int *ptr;
    int value;
    int i;
    int *p;

    if (argc > 1) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        n = (uint32_t)strtol(argv[1], (char **)0x0, 10);
        if (n < 0x65) {
            ptr = (int *)malloc((uint64_t)(n * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n",
                   (uint32_t)n, (uint32_t)(n * 4 & 0xff));
            if (n != 0) {
                loop_end = n * 3;
                value = 1;
                n = 0;
                p = ptr;
                do {
                    *p = value;
                    n = n + value;
                    value = value + 3;
                    p = p + 1;
                } while (value != loop_end + 1);
            }
            printf("Somma: %u\n", (uint32_t)n);
            free(ptr);
            i = 0;
            return (uint64_t)i;
        }
        puts("Troppi elementi");
        i = 1;
        return (uint64_t)i;
    }
    return 1;
}