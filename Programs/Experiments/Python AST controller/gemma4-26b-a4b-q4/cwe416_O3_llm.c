#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv, char **envp) {
    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, NULL, 2, 0);

    char *dest = (char *)calloc(0x20, 1);
    if (dest == NULL) {
        return 1;
    }

    strncpy(dest, argv[1], 0x17);
    dest[0x1c] = (uint8_t)-0x18;
    dest[0x1d] = 0x03;
    dest[0x1e] = 0x00;
    dest[0x1f] = 0x00;

    printf("Sessione %d aperta per %s\n", 1000, dest);

    int logout_check = strcmp(argv[2], "logout");
    if (logout_check == 0) {
        free(dest);
        puts("Logout eseguito");
    }

    if (argc != 3) {
        strtol(argv[3], NULL, 10);
    }

    if (*(int *)(dest + 0x18) == 0) {
        printf("Accesso utente per %s\n", dest);
    } else {
        printf("Accesso amministratore per %s\n", dest);
    }

    if (logout_check != 0) {
        free(dest);
    }

    return 0;
}
