#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    unsigned int n;
    unsigned int sum;
    unsigned int i;
    uint8_t nbytes;
    void *ptr;

    if (argc < 2) {
        return 1;
    }

    setvbuf(stdout, (char *)0, 2, 0);
    n = atoi(argv[1]);

    if (n < 0x65) {
        nbytes = (uint8_t)(n << 2);
        ptr = malloc((unsigned long)nbytes);
        printf("Elementi: %u, byte allocati: %u\n", (unsigned long)n, (unsigned long)nbytes);
        sum = 0;
        for (i = 0; i < n; i = i + 1) {
            *(unsigned int *)((unsigned long)ptr + (unsigned long)i * 4) = i * 3 + 1;
            sum = sum + *(unsigned int *)((unsigned long)ptr + (unsigned long)i * 4);
        }
        printf("Somma: %u\n", (unsigned long)sum);
        free(ptr);
        return 0;
    }
    else {
        puts("Troppi elementi");
        return 1;
    }
}
