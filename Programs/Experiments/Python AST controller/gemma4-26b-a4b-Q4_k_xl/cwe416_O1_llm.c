#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv) {
    int res;
    char *dest;
    long lVar2;
    char *pcVar3;
    uint8_t bVar4;

    bVar4 = 0;
    res = 1;
    if (argc > 2) {
        setvbuf(stdout, NULL, 2, 0);
        dest = (char *)malloc(0x20);
        pcVar3 = dest;
        for (lVar2 = 8; lVar2 != 0; lVar2 = lVar2 - 1) {
            pcVar3[0] = '\0';
            pcVar3[1] = '\0';
            pcVar3[2] = '\0';
            pcVar3[3] = '\0';
            pcVar3 = pcVar3 + (uint64_t)bVar4 * -8 + 4;
        }
        strncpy(dest, argv[1], 0x17);
        *(uint32_t *)(dest + 0x1c) = 1000;
        printf("Sessione %d aperta per %s\n", 1000, dest);
        res = strcmp(argv[2], "logout");
        if (res == 0) {
            free(dest);
            puts("Logout eseguito");
        }
        if (argc > 3) {
            strtol(argv[3], NULL, 10);
        }
        if (*(int32_t *)(dest + 0x18) == 0) {
            printf("Accesso utente per %s\n", dest);
        } else {
            printf("Accesso amministratore per %s\n", dest);
        }
        if (res != 0) {
            free(dest);
            res = 0;
        }
    }
    return res;
}
