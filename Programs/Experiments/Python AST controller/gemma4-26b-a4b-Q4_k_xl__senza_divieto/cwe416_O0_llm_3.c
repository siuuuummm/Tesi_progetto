#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv) {
    int uVar3;

    if (argc < 3) {
        uVar3 = 1;
    }
    else {
        setvbuf(stdout, (char *)0, 2, 0);
        char *dest = (char *)malloc(0x20);
        memset(dest, 0, 0x20);
        strncpy(dest, *(char **)(argv + 1), 0x17);
        dest[0x1c] = (uint8_t)-0x18;
        dest[0x1d] = 0x03;
        dest[0x1e] = 0;
        dest[0x1f] = 0;
        printf("Sessione %d aperta per %s\n", (unsigned long)(*(uint32_t *)(dest + 0x1c)), dest);
        int iVar1 = strcmp(*(char **)(argv + 2), "logout");
        if (iVar1 == 0) {
            free(dest);
            puts("Logout eseguito");
        }
        char *dest_00 = (char *)malloc(0x20);
        memset(dest_00, 0, 0x20);
        strncpy(dest_00, "promemoria", 0x17);
        int iVar2 = 0;
        if (argc < 4) {
            iVar2 = 0;
        }
        else {
            iVar2 = atoi(*(char **)(argv + 3));
        }
        *(int32_t *)(dest_00 + 0x18) = iVar2;
        dest_00[0x1c] = 0x07;
        dest_00[0x1d] = 0;
        dest_00[0x1e] = 0;
        dest_00[0x1f] = 0;
        if (*(int32_t *)(dest + 0x18) == 0) {
            printf("Accesso utente per %s\n", dest);
        }
        else {
            printf("Accesso amministratore per %s\n", dest);
        }
        free(dest_00);
        if (iVar1 != 0) {
            free(dest);
        }
        uVar3 = 0;
    }
    return uVar3;
}
