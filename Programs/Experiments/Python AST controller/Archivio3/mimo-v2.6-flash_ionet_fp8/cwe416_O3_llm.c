#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *buf;
    int logout_cmp;

    if (argc < 3) {
        return 1;
    }
    setvbuf(stdout, (char *)0x0, 2, 0);
    buf = (char *)calloc(0x20, 1);
    strncpy(buf, *(char **)(argv + 1), 0x17);
    buf[0x1c] = -0x18;
    buf[0x1d] = '\x03';
    buf[0x1e] = '\0';
    buf[0x1f] = '\0';
    printf("Sessione %d aperta per %s\n", 1000, buf);
    logout_cmp = strcmp(*(char **)(argv + 2), "logout");
    if (logout_cmp == 0) {
        free(buf);
        puts("Logout eseguito");
    }
    if (argc != 3) {
        strtol(*(char **)(argv + 3), (char **)0x0, 10);
    }
    if (*(int *)(buf + 0x18) == 0) {
        printf("Accesso utente per %s\n", buf);
    }
    else {
        printf("Accesso amministratore per %s\n", buf);
    }
    if (logout_cmp != 0) {
        free(buf);
    }
    return 0;
}