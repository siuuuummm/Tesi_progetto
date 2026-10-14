#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        setvbuf(stdout, NULL, 2, 0);
        long count = strtol(argv[1], NULL, 10);
        if (count < 101) {
            int *ptr = (int *)malloc((uint64_t)(count * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", (uint32_t)count, (uint32_t)(count * 4 & 0xff));
            if (count != 0) {
                int limit = (int)(count * 3);
                int val = 1;
                uint32_t sum = 0;
                int *p = ptr;
                do {
                    *p = val;
                    sum = sum + val;
                    val = val + 3;
                    p = p + 1;
                } while (val != limit + 1);
                printf("Somma: %u\n", sum);
            } else {
                printf("Somma: %u\n", 0);
            }
            free(ptr);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
