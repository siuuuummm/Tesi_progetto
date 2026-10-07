#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char bVar1;
    unsigned int uVar2;
    void *__ptr;
    unsigned int sum;
    unsigned int i;

    if (argc < 2) {
        return 1;
    } else {
        setvbuf(stdout, (char *)0x0, 2, 0);
        uVar2 = (unsigned int)atoi(argv[1]);
        if (uVar2 < 0x65) {
            bVar1 = (unsigned char)(uVar2 << 2);
            __ptr = malloc((unsigned long)bVar1);
            printf("Elementi: %u, byte allocati: %u\n", (unsigned long)uVar2, (unsigned long)bVar1);
            sum = 0;
            for (i = 0; i < uVar2; i = i + 1) {
                *(unsigned int *)((long)__ptr + (unsigned long)i * 4) = i * 3 + 1;
                sum = sum + *(int *)((long)__ptr + (unsigned long)i * 4);
            }
            printf("Somma: %u\n", (unsigned long)sum);
            free(__ptr);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
}