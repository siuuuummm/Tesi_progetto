#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    int term_count_tripled;
    uint32_t count;
    int term;
    int *arr;
    int ret;
    int *p;

    if (1 < argc) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        count = (uint32_t)strtol(argv[1], (char **)0x0, 10);
        if (count < 0x65) {
            arr = (int *)malloc((uint64_t)(count * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", count,
                   (uint8_t)(count * 4));
            if (count != 0) {
                term_count_tripled = count * 3;
                term = 1;
                count = 0;
                p = arr;
                do {
                    *p = term;
                    count = count + term;
                    term = term + 3;
                    p = p + 1;
                } while (term != term_count_tripled + 1);
            }
            printf("Somma: %u\n", count);
            free(arr);
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