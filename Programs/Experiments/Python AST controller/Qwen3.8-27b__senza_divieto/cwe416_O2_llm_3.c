#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *buf;
    int cmp;

    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, NULL, 2, 0);

    buf = (char *)calloc(0x20, 1);
    strncpy(buf, argv[1], 0x17);
    *(int *)(buf + 0x1c) = 0x3e8;
    printf("Sessione %d aperta per %s\n", 0x3e8, buf);

    cmp = strcmp(argv[2], "logout");
    if (cmp == 0) {
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

    if (cmp != 0) {
        free(buf);
    }

    return 0;
}
