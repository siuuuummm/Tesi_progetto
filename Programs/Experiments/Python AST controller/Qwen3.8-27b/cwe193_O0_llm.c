#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* FUN_004004b6: se la stringa ha lunghezza < 0x11 (17), ne copia una versione
 * tronca in un buffer di 0x10 (16) byte con strcpy; altrimenti restituisce NULL. */
char *regista_nome(char *param_1)
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

/* FUN_00400507: main */
int main(int param_1, char **param_2)
{
    char *__s;
    size_t sVar1;
    int local_c;

    setvbuf(stdout, (char *)0x0, 2, 0);
    for (local_c = 1; local_c < param_1; local_c = local_c + 1) {
        __s = registra_nome(*(char **)(param_2 + (long)local_c * 8));
        if (__s == (char *)0x0) {
            sVar1 = strlen(*(char **)(param_2 + (long)local_c * 8));
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
