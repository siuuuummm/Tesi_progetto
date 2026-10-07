#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
    int cmp_result;
    char *session;

    if (argc < 3) {
        return 1;
    }
    setvbuf(stdout, (char *)0x0, 2, 0);
    session = (char *)calloc(0x20, 1);
    strncpy(session, argv[1], 0x17);
    session[0x1c] = -0x18;
    session[0x1d] = '\x03';
    session[0x1e] = '\0';
    session[0x1f] = '\0';
    printf("Sessione %d aperta per %s\n", 1000, session);
    cmp_result = strcmp(argv[2], "logout");
    if (cmp_result == 0) {
        free(session);
        puts("Logout eseguito");
    }
    if (argc != 3) {
        strtol(argv[3], 0, 10);
    }
    if (*(int *)(session + 0x18) == 0) {
        printf("Accesso utente per %s\n", session);
    }
    else {
        printf("Accesso amministratore per %s\n", session);
    }
    if (cmp_result != 0) {
        free(session);
    }
    return 0;
}