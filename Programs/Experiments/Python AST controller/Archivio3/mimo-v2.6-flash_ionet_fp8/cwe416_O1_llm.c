#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern long __isoc23_strtol(const char *nptr, char **endptr, int base);

int main(int param_1, long param_2)
{
    int iVar1;
    char *__dest;
    long lVar2;
    char *pcVar3;
    uint8_t bVar4;

    bVar4 = 0;
    iVar1 = 1;
    if (2 < param_1) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        __dest = (char *)malloc(0x20);
        pcVar3 = __dest;
        for (lVar2 = 8; lVar2 != 0; lVar2 = lVar2 + -1) {
            pcVar3[0] = '\0';
            pcVar3[1] = '\0';
            pcVar3[2] = '\0';
            pcVar3[3] = '\0';
            pcVar3 = pcVar3 + (uint64_t)bVar4 * -8 + 4;
        }
        strncpy(__dest, *(char **)(param_2 + 8), 0x17);
        *(int *)(__dest + 0x1c) = 0x3e8;
        printf("Sessione %d aperta per %s\n", 1000, __dest);
        iVar1 = strcmp(*(char **)(param_2 + 0x10), "logout");
        if (iVar1 == 0) {
            free(__dest);
            puts("Logout eseguito");
        }
        if (3 < param_1) {
            __isoc23_strtol(*(char **)(param_2 + 0x18), (char **)0x0, 10);
        }
        if (*(int *)(__dest + 0x18) == 0) {
            printf("Accesso utente per %s\n", __dest);
        }
        else {
            printf("Accesso amministratore per %s\n", __dest);
        }
        if (iVar1 != 0) {
            free(__dest);
            iVar1 = 0;
        }
    }
    return iVar1;
}