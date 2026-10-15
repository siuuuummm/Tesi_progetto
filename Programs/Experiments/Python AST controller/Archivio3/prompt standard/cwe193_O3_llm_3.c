#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int param_1, char **param_2)
{
    char **puVar6;
    char **puVar1;
    char *__s;
    size_t sVar3;
    char *__ptr;

    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < param_1) {
        puVar6 = (char **)(param_2 + 1);
        puVar1 = (char **)(param_2 + 2 + (param_1 - 2));
        do {
            __s = *puVar6;
            sVar3 = strlen(__s);
            if (0x10 < sVar3) {
                puVar6 = puVar6 + 1;
                printf("Nome troppo lungo: %zu caratteri\n", sVar3);
                continue;
            }
            __ptr = (char *)malloc(0x10);
            memcpy(__ptr, __s, sVar3 + 1);
            printf("Registrato: %s (%zu caratteri)\n", __ptr, sVar3);
            puVar6 = puVar6 + 1;
            free(__ptr);
            if (puVar6 == puVar1) {
                return 0;
            }
        } while (puVar6 != puVar1);
    }
    return 0;
}
