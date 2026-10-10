#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    unsigned int count;
    int i;
    int *buf;
    uint64_t ret;
    int limit;
    int *p;

    if (argc > 1) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        count = (unsigned int)strtol(argv[1], NULL, 10);
        if (count < 0x65) {
            buf = (int *)malloc((unsigned long)(count * 4 & 0xff));
            printf("Elementi: %u, byte allocati: %u\n", count, count * 4 & 0xff);
            if (count != 0) {
                limit = count * 3;
                i = 1;
                count = 0;
                p = buf;
                do {
                    *p = i;
                    count = count + i;
                    i = i + 3;
                    p = p + 1;
                } while (i != limit + 1);
            }
            printf("Somma: %u\n", count);
            free(buf);
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
