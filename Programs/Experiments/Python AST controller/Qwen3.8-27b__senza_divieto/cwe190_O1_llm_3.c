#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    unsigned int n;
    unsigned char alloc;
    int i;
    int sum;
    int *arr;
    int *p;

    if (argc > 1) {
        setvbuf(stdout, NULL, _IONBF, 0);
        n = strtol(argv[1], NULL, 10);
        if (n <= 100) {
            alloc = (unsigned char)(n * 4);
            arr = (int *)malloc(alloc);
            printf("Elementi: %u, byte allocati: %u\n", n, (unsigned int)alloc);
            if (n != 0) {
                i = 1;
                sum = 0;
                p = arr;
                do {
                    *p = i;
                    sum = sum + i;
                    i = i + 3;
                    p = p + 1;
                } while (i != n * 3 + 1);
            }
            printf("Somma: %u\n", (unsigned int)sum);
            free(arr);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
