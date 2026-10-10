#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, long argv_long)
{
    char **argv = (char **)argv_long;
    int iVar1;
    char *__dest;
    long lVar2;
    char *pcVar3;

    iVar1 = 1;
    if (2 < argc) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        __dest = (char *)malloc(0x20);
        pcVar3 = __dest;
        for (lVar2 = 8; lVar2 != 0; lVar2 = lVar2 + -1) {
            pcVar3[0] = '\0';
            pcVar3[1] = '\0';
            pcVar3[2] = '\0';
            pcVar3[3] = '\0';
            pcVar3 = pcVar3 + 4;
        }
        strncpy(__dest, *(char **)((long)argv + 8), 0x17);
        *(uint32_t *)(__dest + 0x1c) = 0x3e8;
        printf("Sessione %d aperta per %s\n", 1000, __dest);
        iVar1 = strcmp(*(char **)((long)argv + 0x10), "logout");
        if (iVar1 == 0) {
            free(__dest);
            puts("Logout eseguito");
        }
        if (3 < argc) {
            strtol(*(char **)((long)argv + 0x18), 0, 10);
        }
        if (*(int *)(__dest + 0x18) == 0) {
            printf("Accesso utente per %s\n", __dest);
        } else {
            printf("Accesso amministratore per %s\n", __dest);
        }
        if (iVar1 != 0) {
            free(__dest);
            iVar1 = 0;
        }
    }
    return iVar1;
}
