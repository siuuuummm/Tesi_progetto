#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int ret;
    int cmp_result;
    char *session;

    ret = 1;
    if (argc > 2) {
        setvbuf(stdout, (char *)0x0, 2, 0);
        session = (char *)malloc(0x20);
        memset(session, 0, 0x20);
        strncpy(session, argv[1], 0x17);
        *(int *)(session + 0x1c) = 0x3e8;
        printf("Sessione %d aperta per %s\n", 1000, session);
        cmp_result = strcmp(argv[2], "logout");
        if (cmp_result == 0) {
            free(session);
            puts("Logout eseguito");
        }
        if (argc > 3) {
            strtol(argv[3], (char **)0x0, 10);
        }
        if (*(int *)(session + 0x18) == 0) {
            printf("Accesso utente per %s\n", session);
        }
        else {
            printf("Accesso amministratore per %s\n", session);
        }
        if (cmp_result != 0) {
            free(session);
            cmp_result = 0;
        }
        ret = cmp_result;
    }
    return ret;
}
