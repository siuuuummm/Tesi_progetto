#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    int *ptr;
    int target;
    int cur;
    unsigned int sum;
    unsigned int n;
    int *p;

    if (1 < argc) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        n = (unsigned int)strtol(argv[1], NULL, 10);
        if (n < 0x65) {
            ptr = (int *)malloc((n * 4) & 0xff);
            printf("Elementi: %u, byte allocati: %u\n", (unsigned)n,
                   (unsigned)((n * 4) & 0xff));
            if (n != 0) {
                target = n * 3;
                cur = 1;
                sum = 0;
                p = ptr;
                do {
                    *p = cur;
                    sum = sum + cur;
                    cur = cur + 3;
                    p = p + 1;
                } while (cur != target + 1);
            }
            else {
                sum = 0;
            }
            printf("Somma: %u\n", (unsigned)sum);
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
