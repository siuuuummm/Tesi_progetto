#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc > 1) {
        setvbuf(stdout, NULL, 2, 0);
        unsigned int n = strtol(argv[1], NULL, 10);
        if (n < 0x65) {
            int *arr = malloc((n * 4) & 0xff);
            printf("Elementi: %u, byte allocati: %u\n", n, (unsigned char)(n * 4));
            unsigned int sum = 0;
            if (n != 0) {
                int target = n * 3;
                for (int i = 1; i <= target; i += 3) {
                    arr[i / 3] = i;
                    sum += i;
                }
            }
            printf("Somma: %u\n", sum);
            free(arr);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
