#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    int iVar1 = 1;
    char *dest;

    if (argc > 2) {
        setvbuf(stdout, (char *)0, 2, 0);
        dest = (char *)malloc(0x20);
        if (dest == NULL) {
            return 1;
        }

        // The following loop clears 32 bytes (8 * 4)
        memset(dest, 0, 32);

        strncpy(dest, argv[1], 0x17);
        
        // Writing 0x3e8 (1000) at offset 0x1c
        // This also sets dest[0x1d], dest[0x1e], dest[0x1f] due to 4-byte write
        *(uint32_t *)(dest + 0x1c) = 0x3e8;

        printf("Sessione %d aperta per %s\n", 1000, dest);

        iVar1 = strcmp(argv[2], "logout");
        if (iVar1 == 0) {
            free(dest);
            puts("Logout eseguito");
        }

        if (argc > 3) {
            strtol(argv[3], NULL, 10);
        }

        // Use-after-free vulnerability if argv[2] was "logout"
        if (*(int *)(dest + 0x18) == 0) {
            printf("Accesso utente per %s\n", dest);
        } else {
            printf("Accesso amministratore per %s\n", dest);
        }

        if (iVar1 != 0) {
            free(dest);
            iVar1 = 0;
        }
    }

    return iVar1;
}
