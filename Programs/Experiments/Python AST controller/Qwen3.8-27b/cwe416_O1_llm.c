#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int exit_code = 1;
    char *buf;
    char *p;
    long i;
    int cmp_logout;

    if (2 < argc) {
        setvbuf(stdout, NULL, 2, 0);
        buf = malloc(0x20);
        p = buf;
        for (i = 8; i != 0; i = i + -1) {
            p[0] = '\0';
            p[1] = '\0';
            p[2] = '\0';
            p[3] = '\0';
            p = p + 4;
        }
        strncpy(buf, argv[1], 0x17);
        buf[0x1c] = -0x18;
        buf[0x1d] = '\x03';
        buf[0x1e] = '\0';
        buf[0x1f] = '\0';
        printf("Sessione %d aperta per %s\n", 1000, buf);
        cmp_logout = strcmp(argv[2], "logout");
        if (cmp_logout == 0) {
            free(buf);
            puts("Logout eseguito");
        }
        if (3 < argc) {
            strtol(argv[3], 0, 10);
        }
        if (*(int *)(buf + 0x18) == 0) {
            printf("Accesso utente per %s\n", buf);
        }
        else {
            printf("Accesso amministratore per %s\n", buf);
        }
        if (cmp_logout != 0) {
            free(buf);
            exit_code = 0;
        }
    }
    return exit_code;
}
