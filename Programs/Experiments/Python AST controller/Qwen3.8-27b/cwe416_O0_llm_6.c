#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    int iVar1;
    int iVar2;
    char *dest;
    char *dest_00;

    if (argc < 3) {
        return 1;
    }
    else {
        setvbuf(stdout, NULL, 2, 0);
        dest = (char *)malloc(0x20);
        memset(dest, 0, 0x20);
        strncpy(dest, argv[1], 0x17);
        *(int *)(dest + 0x1c) = 0x3e8;
        printf("Sessione %d aperta per %s\n", *(int *)(dest + 0x1c), dest);
        iVar1 = strcmp(argv[2], "logout");
        if (iVar1 == 0) {
            free(dest);
            puts("Logout eseguito");
        }
        dest_00 = (char *)malloc(0x20);
        memset(dest_00, 0, 0x20);
        strncpy(dest_00, "promemoria", 0x17);
        if (argc < 4) {
            iVar2 = 0;
        }
        else {
            iVar2 = atoi(argv[3]);
        }
        *(int *)(dest_00 + 0x18) = iVar2;
        *(int *)(dest_00 + 0x1c) = 0x7;
        if (*(int *)(dest + 0x18) == 0) {
            printf("Accesso utente per %s\n", dest);
        }
        else {
            printf("Accesso amministratore per %s\n", dest);
        }
        free(dest_00);
        if (iVar1 != 0) {
            free(dest);
        }
        return 0;
    }
}
