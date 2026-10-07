#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, NULL, 2, 0);

    uint8_t *dest = (uint8_t *)calloc(0x20, 1);
    if (dest == NULL) {
        return 1;
    }

    strncpy((char *)dest, argv[1], 0x17);

    // The assembly shows: MOV dword ptr [RBX + 0x1c], 0x3e8
    // This sets dest[0x1c]=0xe8, dest[0x1d]=0x03, dest[0x1e]=0x00, dest[0x1f]=0x00.
    // 0x3e8 is 1000.
    *(uint32_t *)(dest + 0x1c) = 1000;

    printf("Sessione %d aperta per %s\n", 1000, (char *)dest);

    int logout_check = strcmp(argv[2], "logout");

    if (logout_check == 0) {
        free(dest);
        puts("Logout eseguito");
    }

    if (argc != 3) {
        // Note: if argc < 4, this is an OOB read on argv.
        strtol(argv[3], NULL, 10);
    }

    if (*(int *)(dest + 0x18) == 0) {
        printf("Accesso utente per %s\n", (char *)dest);
    } else {
        printf("Accesso amministratore per %s\n", (char *)dest);
    }

    if (logout_check != 0) {
        free(dest);
    }

    return 0;
}
