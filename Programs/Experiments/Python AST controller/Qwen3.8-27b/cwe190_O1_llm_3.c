#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        setvbuf(stdout, NULL, 2, 0);
        unsigned int n = strtol(argv[1], NULL, 10);
        if (n < 0x65)
        {
            int *buf = (int *)malloc((n * 4) & 0xff);
            printf("Elementi: %u, byte allocati: %u\n", n, (n * 4) & 0xff);
            unsigned int sum = 0;
            if (n != 0)
            {
                int bound = (int)n * 3;
                int value = 1;
                int *p = buf;
                do
                {
                    *p = value;
                    sum = sum + value;
                    value = value + 3;
                    p = p + 1;
                } while (value != bound + 1);
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
