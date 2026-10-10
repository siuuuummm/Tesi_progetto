#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Copia il nome se lungo al massimo 15 caratteri (0x11 = 17, confronto < 0x11),
   altrimenti ritorna NULL */
static char *duplicate_name_if_short(const char *param_1)
{
    size_t sVar1;
    char *__dest;

    sVar1 = strlen(param_1);
    if (sVar1 < 0x11) {
        __dest = (char *)malloc(0x10);
        strcpy(__dest, param_1);
    }
    else {
        __dest = (char *)0x0;
    }
    return __dest;
}

int main(int param_1, char **param_2)
{
    char *__s;
    size_t sVar1;
    int local_c;

    setvbuf(stdout, (char *)0x0, 2, 0);
    for (local_c = 1; local_c < param_1; local_c = local_c + 1) {
        __s = duplicate_name_if_short(param_2[local_c]);
        if (__s == (char *)0x0) {
            sVar1 = strlen(param_2[local_c]);
            printf("Nome troppo lungo: %zu caratteri\n", sVar1);
        }
        else {
            sVar1 = strlen(__s);
            printf("Registrato: %s (%zu caratteri)\n", __s, sVar1);
            free(__s);
        }
    }
    return 0;
}
