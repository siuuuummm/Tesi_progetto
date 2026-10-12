#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    int iVar1;
    unsigned int n;
    int iVar3;
    int *ptr;
    unsigned int sum;
    int *p;
    int ret;

    if (1 < argc) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        n = (unsigned int)strtol(argv[1], (char **)0x0, 10);
        if (n < 0x65) {
            ptr = (int *)malloc((unsigned long)(n * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n",
                   (unsigned long)n,
                   (unsigned long)(unsigned char)(n * 4));
            sum = n;
            if (n != 0) {
                iVar1 = n * 3;
                iVar3 = 1;
                sum = 0;
                p = ptr;
                do {
                    *p = iVar3;
                    sum = sum + iVar3;
                    iVar3 = iVar3 + 3;
                    p = p + 1;
                } while (iVar3 != iVar1 + 1);
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