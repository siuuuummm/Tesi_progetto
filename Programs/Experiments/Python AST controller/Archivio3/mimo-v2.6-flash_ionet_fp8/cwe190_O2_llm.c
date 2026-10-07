#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

extern long int __isoc23_strtol(const char *__restrict nptr,
                                 char **__restrict endptr, int base);

int main(int argc, char **argv)
{
    int limit;
    unsigned int count;
    int step;
    int *buffer;
    uint64_t ret;
    int *cursor;

    if (1 < argc) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        count = __isoc23_strtol(argv[1], 0, 10);
        if (count < 0x65) {
            buffer = (int *)malloc((uint64_t)(count * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n",
                   (uint64_t)count, (uint64_t)(uint8_t)(count * 4));
            if (count != 0) {
                limit = count * 3;
                step = 1;
                count = 0;
                cursor = buffer;
                do {
                    *cursor = step;
                    count = count + step;
                    step = step + 3;
                    cursor = cursor + 1;
                } while (step != limit + 1);
            }
            printf("Somma: %u\n", (uint64_t)count);
            free(buffer);
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
