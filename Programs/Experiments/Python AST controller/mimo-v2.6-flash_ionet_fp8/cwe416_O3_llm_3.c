#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern long int __isoc23_strtol(const char *nptr, char **endptr, int base);

int main(int argc, char **argv)
{
    char *session;
    int logout_cmp;

    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, (char *)0x0, 2, 0);

    session = (char *)calloc(0x20, 1);
    strncpy(session, argv[1], 0x17);
    *(uint32_t *)(session + 0x1c) = 1000;

    printf("Sessione %d aperta per %s\n", 1000, session);

    logout_cmp = strcmp(argv[2], "logout");
    if (logout_cmp == 0) {
        free(session);
        puts("Logout eseguito");
    }

    if (argc != 3) {
        __isoc23_strtol(argv[3], (char **)0x0, 10);
    }

    if (*(int *)(session + 0x18) == 0) {
        printf("Accesso utente per %s\n", session);
    } else {
        printf("Accesso amministratore per %s\n", session);
    }

    if (logout_cmp != 0) {
        free(session);
    }

    return 0;
}
