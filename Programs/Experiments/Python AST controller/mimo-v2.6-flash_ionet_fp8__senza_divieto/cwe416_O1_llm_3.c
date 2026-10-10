#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern long __isoc23_strtol(const char *nptr, char **endptr, int base);

int main(int argc, char **argv)
{
    int ret;
    char *buf;

    ret = 1;
    if (argc > 2) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        buf = (char *)malloc(0x20);
        memset(buf, 0, 0x20);
        strncpy(buf, argv[1], 0x17);
        *(int *)(buf + 0x1c) = 0x3e8;
        printf("Sessione %d aperta per %s\n", 0x3e8, buf);
        ret = strcmp(argv[2], "logout");
        if (ret == 0) {
            free(buf);
            puts("Logout eseguito");
        }
        if (argc > 3) {
            __isoc23_strtol(argv[3], (char **)0x0, 10);
        }
        if (*(int *)(buf + 0x18) == 0) {
            printf("Accesso utente per %s\n", buf);
        }
        else {
            printf("Accesso amministratore per %s\n", buf);
        }
        if (ret != 0) {
            free(buf);
            ret = 0;
        }
    }
    return ret;
}
