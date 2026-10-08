#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, NULL, 2, 0);
    char *__dest = (char *)calloc(0x20, 1);
    if (__dest == NULL) {
        return 1;
    }

    strncpy(__dest, argv[1], 0x17);
    __dest[0x1c] = (char)-0x18;
    __dest[0x1d] = 0x03;
    __dest[0x1e] = '\0';
    __dest[0x1f] = '\0';

    printf("Sessione %d aperta per %s\n", 1000, __dest);

    int iVar2 = strcmp(argv[2], "logout");
    if (iVar2 == 0) {
        free(__dest);
        puts("Logout eseguito");
    }

    if (argc != 3) {
        strtol(argv[3], NULL, 10);
    }

    if (*(int *)(__dest + 0x18) == 0) {
        printf("Accesso utente per %s\n", __dest);
    } else {
        printf("Accesso amministratore per %s\n", __dest);
    }

    if (iVar2 != 0) {
        free(__dest);
    }

    return 0;
}
