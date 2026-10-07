#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern long __isoc23_strtol(const char *nptr, char **endptr, int base);

int main(int argc, char **argv)
{
    unsigned int count;
    int three_times_count;
    int *buffer;
    int status;
    unsigned int sum;
    int value;
    int *cursor;

    if (argc <= 1) {
        return 1;
    }
    setvbuf(stdout, (char *)0x0, 2, 0);
    count = (unsigned int)__isoc23_strtol(argv[1], 0, 10);
    if (count < 0x65) {
        buffer = (int *)malloc((size_t)(count * 4 & 0xff));
        printf("Elementi: %u, byte allocati: %u\n",
               count, count * 4 & 0xff);
        sum = count;
        if (count != 0) {
            three_times_count = count * 3;
            value = 1;
            sum = 0;
            cursor = buffer;
            do {
                *cursor = value;
                sum = sum + value;
                value = value + 3;
                cursor = cursor + 1;
            } while (value != three_times_count + 1);
        }
        printf("Somma: %u\n", sum);
        free(buffer);
        status = 0;
    } else {
        puts("Troppi elementi");
        status = 1;
    }
    return status;
}