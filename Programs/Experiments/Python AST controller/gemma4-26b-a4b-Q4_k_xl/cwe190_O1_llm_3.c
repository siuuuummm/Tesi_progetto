#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    uint32_t count;
    int limit;
    int val;
    uint32_t sum;
    int *ptr;
    int *p;

    if (argc > 1) {
        setvbuf(stdout, NULL, 2, 0);
        count = (uint32_t)strtol(argv[1], NULL, 10);
        if (count < 0x65) {
            ptr = (int *)malloc((size_t)(count * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", count, (unsigned int)(count * 4 & 0xff));
            if (count != 0) {
                limit = count * 3;
                val = 1;
                sum = 0;
                p = ptr;
                do {
                    *p = val;
                    sum = sum + val;
                    val = val + 3;
                    p = p + 1;
                } while (val != limit + 1);
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
