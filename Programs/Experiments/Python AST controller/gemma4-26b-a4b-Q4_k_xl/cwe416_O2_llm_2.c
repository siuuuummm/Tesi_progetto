#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, NULL, 2, 0);

    char *buf = (char *)calloc(0x20, 1);
    if (buf == NULL) {
        return 1;
    }

    strncpy(buf, argv[1], 0x17);
    buf[0x1c] = (uint8_t)-0x18;
    buf[0x1d] = 0x03;
    buf[0x1e] = 0x00;
    buf[0x1f] = 0x00;

    printf("Sessione %d aperta per %s\n", 1000, buf);

    int logout_check = strcmp(argv[2], "logout");
    if (logout_check == 0) {
        free(buf);
        puts("Logout eseguito");
    }

    if (argc != 3) {
        strtol(argv[3], NULL, 10);
    }

    if (*(int *)(buf + 0x18) == 0) {
        printf("Accesso utente per %s\n", buf);
    } else {
        printf("Accesso amministratore per %s\n", buf);
    }

    if (logout_check != 0) {
        free(buf);
    }

    return 0;
}
