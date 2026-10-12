#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    int iVar1;
    char *__dest;

    iVar1 = 1;
    if (argc > 2)
    {
        setvbuf(stdout, (char *)0, 2, 0);
        __dest = (char *)malloc(0x20);
        memset(__dest, 0, 0x20);
        strncpy(__dest, *(char **)(argv + 1), 0x17);
        *(uint32_t *)(__dest + 0x1c) = 0x3e8;
        printf("Sessione %d aperta per %s\n", 1000, __dest);
        iVar1 = strcmp(*(char **)(argv + 2), "logout");
        if (iVar1 == 0)
        {
            free(__dest);
            puts("Logout eseguito");
        }
        if (argc > 3)
        {
            strtol(*(char **)(argv + 3), 0, 10);
        }
        if (*(int *)(__dest + 0x18) == 0)
        {
            printf("Accesso utente per %s\n", __dest);
        }
        else
        {
            printf("Accesso amministratore per %s\n", __dest);
        }
        if (iVar1 != 0)
        {
            free(__dest);
            iVar1 = 0;
        }
    }
    return iVar1;
}
