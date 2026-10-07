#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        setvbuf(stdout, NULL, _IONBF, 0);
        unsigned int n = strtol(argv[1], NULL, 10);
        if (n < 0x65)
        {
            int *buf = malloc((n * 4) & 0xff);
            printf("Elementi: %u, byte allocati: %u\n", n, (uint8_t)(n * 4));
            unsigned int sum = 0;
            if (n != 0)
            {
                int v = 1;
                int end = n * 3;
                int *p = buf;
                do
                {
                    *p = v;
                    sum += v;
                    v += 3;
                    p++;
                } while (v != end + 1);
            }
            printf("Somma: %u\n", sum);
            free(buf);
            return 0;
        }
        else
        {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
