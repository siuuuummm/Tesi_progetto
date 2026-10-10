#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern long int __isoc23_strtol(const char *nptr, char **endptr, int base);

int main(int argc, char **argv)
{
    char *session_buf;
    int logout_cmp;

    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, (char *)0x0, 2, 0);
    session_buf = (char *)calloc(0x20, 1);
    strncpy(session_buf, argv[1], 0x17);
    *(uint32_t *)(session_buf + 0x1c) = 0x3e8;
    printf("Sessione %d aperta per %s\n", 0x3e8, session_buf);

    logout_cmp = strcmp(argv[2], "logout");
    if (logout_cmp == 0) {
        free(session_buf);
        puts("Logout eseguito");
    }

    if (argc != 3) {
        __isoc23_strtol(argv[3], (char **)0x0, 10);
    }

    if (*(int *)(session_buf + 0x18) == 0) {
        printf("Accesso utente per %s\n", session_buf);
    } else {
        printf("Accesso amministratore per %s\n", session_buf);
    }

    if (logout_cmp != 0) {
        free(session_buf);
    }

    return 0;
}
