#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern long __isoc23_strtol(const char *nptr, char **endptr, int base);

int main(int argc, char **argv)
{
    char *buf;
    int logout_cmp;

    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, (char *)0x0, 2, 0);

    buf = (char *)calloc(0x20, 1);
    strncpy(buf, argv[1], 0x17);
    *(uint32_t *)(buf + 0x1c) = 0x3e8;

    printf("Sessione %d aperta per %s\n", 1000, buf);

    logout_cmp = strcmp(argv[2], "logout");
    if (logout_cmp == 0) {
        free(buf);
        puts("Logout eseguito");
    }

    if (argc != 3) {
        __isoc23_strtol(argv[3], (char **)0x0, 10);
    }

    if (*(int *)(buf + 0x18) == 0) {
        printf("Accesso utente per %s\n", buf);
    } else {
        printf("Accesso amministratore per %s\n", buf);
    }

    if (logout_cmp != 0) {
        free(buf);
    }

    return 0;
}
