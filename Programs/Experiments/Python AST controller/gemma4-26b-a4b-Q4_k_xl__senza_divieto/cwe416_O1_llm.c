#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv) {
    int iVar1 = 1;
    if (argc > 2) {
        setvbuf(stdout, NULL, 2, 0);
        char *dest = (char *)malloc(0x20);
        
        char *pcVar3 = dest;
        for (long lVar2 = 8; lVar2 != 0; lVar2 = lVar2 - 1) {
            pcVar3[0] = '\0';
            pcVar3[1] = '\0';
            pcVar3[2] = '\0';
            pcVar3[3] = '\0';
            pcVar3 = pcVar3 + (uint64_t)0 * -8 + 4;
        }

        strncpy(dest, argv[2], 0x17);
        dest[0x1c] = (uint8_t)-0x18;
        dest[0x1d] = '\x03';
        dest[0x1e] = '\0';
        dest[0x1f] = '\0';

        printf("Sessione %d aperta per %s\n", 1000, dest);

        int strcmp_res = strcmp(argv[1], "logout");
        if (strcmp_res == 0) {
            free(dest);
            puts("Logout eseguito");
        }

        if (argc > 3) {
            strtol(argv[3], NULL, 10);
        }

        if (*(uint32_t *)(dest + 0x18) == 0) {
            printf("Accesso utente per %s\n", dest);
        } else {
            printf("Accesso amministratore per %s\n", dest);
        }

        if (strcmp_res != 0) {
            free(dest);
            iVar1 = 0;
        }
    }
    return iVar1;
}
