#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern long int __isoc23_strtol(const char *restrict __nptr, char **restrict __endptr, int __base);

int main(int argc, char **argv)
{
    int result;
    char *buf;
    int logout_status;

    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, (char *)0x0, 2, 0);

    buf = (char *)calloc(0x20, 1);
    strncpy(buf, argv[1], 0x17);
    *(int *)(buf + 0x1c) = 1000;

    printf("Sessione %d aperta per %s\n", 1000, buf);

    logout_status = strcmp(argv[2], "logout");
    if (logout_status == 0) {
        free(buf);
        puts("Logout eseguito");
    }

    if (argc != 3) {
        __isoc23_strtol(argv[3], (char **)0x0, 10);
    }

    if (*(int *)(buf + 0x18) == 0) {
        printf("Accesso utente per %s\n", buf);
    }
    else {
        printf("Accesso amministratore per %s\n", buf);
    }

    if (logout_status != 0) {
        free(buf);
    }

    result = 0;
    return result;
}
