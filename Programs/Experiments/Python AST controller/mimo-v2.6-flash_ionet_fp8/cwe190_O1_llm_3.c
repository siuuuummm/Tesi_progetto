#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    unsigned int count;
    int i;
    int *ptr;
    int ret;
    int step;
    int *p;
    unsigned int sum;

    if (argc > 1) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        count = (unsigned int)strtol(argv[1], 0, 10);
        if (count < 0x65) {
            ptr = (int *)malloc((unsigned long)(count * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n",
                   (unsigned long)count,
                   (unsigned long)(count * 4 & 0xff));
            sum = 0;
            if (count != 0) {
                i = count * 3;
                step = 1;
                p = ptr;
                do {
                    *p = step;
                    sum = sum + step;
                    step = step + 3;
                    p = p + 1;
                } while (step != i + 1);
            }
            printf("Somma: %u\n", (unsigned long)sum);
            free(ptr);
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