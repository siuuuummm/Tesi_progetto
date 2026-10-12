#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv) {
    int iVar1 = 1;
    char *buffer;
    long lVar2;
    char *pcVar3;
    uint8_t bVar4 = 0;

    if (argc > 2) {
        setvbuf(stdout, NULL, 2, 0);
        buffer = (char *)malloc(0x20);
        pcVar3 = buffer;
        for (lVar2 = 8; lVar2 != 0; lVar2 = lVar2 - 1) {
            pcVar3[0] = '\0';
            pcVar3[1] = '\0';
            pcVar3[2] = '\0';
            pcVar3[3] = '\0';
            pcVar3 = pcVar3 + (uint64_t)bVar4 * -8 + 4;
        }
        strncpy(buffer, argv[1], 0x17);
        buffer[0x1c] = (uint8_t)-0x18;
        buffer[0x1d] = 0x03;
        buffer[0x1e] = '\0';
        buffer[0x1f] = '\0';
        printf("Sessione %d aperta per %s\n", 1000, buffer);
        iVar1 = strcmp(argv[2], "logout");
        if (iVar1 == 0) {
            free(buffer);
            puts("Logout eseguito");
        }
        if (argc > 3) {
            strtol(argv[3], NULL, 10);
        }
        if (*(int *)(buffer + 0x18) == 0) {
            printf("Accesso utente per %s\n", buffer);
        } else {
            printf("Accesso amministratore per %s\n", buffer);
        }
        if (iVar1 != 0) {
            free(buffer);
            iVar1 = 0;
        }
    }
    return iVar1;
}
