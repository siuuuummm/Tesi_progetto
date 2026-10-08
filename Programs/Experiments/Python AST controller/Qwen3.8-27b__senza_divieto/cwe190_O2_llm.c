#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc > 1) {
        setvbuf(stdout, (char *)0, 2, 0);
        unsigned int n = (unsigned int)strtol(argv[1], 0, 10);
        if (n < 0x65) {
            int *ptr = (int *)malloc(((unsigned long)(n * 4) & 0xff));
            printf("Elementi: %u, byte allocati: %u\n",
                   (unsigned long)n,
                   (unsigned long)(unsigned char)(n * 4));
            unsigned int sum = 0;
            if (n != 0) {
                int limit = n * 3 + 1;
                int i = 1;
                int *p = ptr;
                do {
                    *p = i;
                    sum = sum + (unsigned int)i;
                    i = i + 3;
                    p = p + 1;
                } while (i != limit);
            }
            printf("Somma: %u\n", (unsigned long)sum);
            free(ptr);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
