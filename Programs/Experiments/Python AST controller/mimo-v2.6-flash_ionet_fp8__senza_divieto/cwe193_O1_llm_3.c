#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FUN_004004b6: registra una copia del nome solo se la lunghezza e' < 0x11 */
char *duplicate_name_if_short(char *param_1)
{
    size_t sVar1;
    char *__dest;

    sVar1 = strlen(param_1);
    __dest = (char *)0x0;
    if (sVar1 < 0x11) {
        __dest = (char *)malloc(0x10);
        strcpy(__dest, param_1);
    }
    return __dest;
}

/* FUN_004004f1: main */
int main(int param_1, long param_2)
{
    char *__s;
    char *__s_00;
    size_t sVar1;
    unsigned long long *puVar2;

    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < param_1) {
        puVar2 = (unsigned long long *)(param_2 + 8);
        do {
            __s = (char *)*puVar2;
            __s_00 = duplicate_name_if_short(__s);
            if (__s_00 == (char *)0x0) {
                sVar1 = strlen(__s);
                printf("Nome troppo lungo: %zu caratteri\n", sVar1);
            } else {
                sVar1 = strlen(__s_00);
                printf("Registrato: %s (%zu caratteri)\n", __s_00, sVar1);
                free(__s_00);
            }
            puVar2 = puVar2 + 1;
        } while (puVar2 != (unsigned long long *)(param_2 + 0x10 + (unsigned long)(param_1 - 2) * 8));
    }
    return 0;
}
