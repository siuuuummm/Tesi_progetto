#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    uint32_t n;
    int *ptr;
    int limite;
    int valore;
    int *p;
    unsigned somma;

    if (argc > 1) {
        setvbuf(stdout, NULL, 2, 0);
        n = (uint32_t)strtol(argv[1], NULL, 10);
        if (n < 0x65) {
            ptr = (int *)malloc(n * 4 & 0xff);
            printf("Elementi: %u, byte allocati: %u\n", (unsigned)n, (unsigned)(n * 4 & 0xff));
            if (n != 0) {
                limite = n * 3;
                valore = 1;
                somma = 0;
                p = ptr;
                do {
                    *p = valore;
                    somma += valore;
                    valore += 3;
                    p++;
                } while (valore != limite + 1);
            }
            printf("Somma: %u\n", (unsigned)somma);
            free(ptr);
            return 0;
        }
        puts("Troppi elementi");
        return 1;
    }
    return 1;
}
