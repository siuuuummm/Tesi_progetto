#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    unsigned char nbyte;
    uint32_t n;
    int ret;
    void *buf;
    uint32_t i;
    uint32_t sum;

    if (argc < 2) {
        ret = 1;
    }
    else {
        setvbuf(stdout, (char *)0, 2, 0);
        n = (uint32_t)atoi(argv[1]);
        if (n < 0x65) {
            nbyte = (unsigned char)(n << 2);
            buf = malloc((size_t)nbyte);
            printf("Elementi: %u, byte allocati: %u\n", (unsigned long)n, (unsigned long)nbyte);
            sum = 0;
            for (i = 0; i < n; i = i + 1) {
                *(uint32_t *)((long)buf + (unsigned long)i * 4) = i * 3 + 1;
                sum = sum + *(int32_t *)((long)buf + (unsigned long)i * 4);
            }
            printf("Somma: %u\n", (unsigned long)sum);
            free(buf);
            ret = 0;
        }
        else {
            puts("Troppi elementi");
            ret = 1;
        }
    }
    return ret;
}
