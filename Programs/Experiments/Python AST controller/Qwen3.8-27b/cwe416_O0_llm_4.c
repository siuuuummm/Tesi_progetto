#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char *session;
    char *note;
    int is_logout;
    int note_value;

    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, (char *)0x0, 2, 0);

    session = (char *)malloc(0x20);
    memset(session, 0, 0x20);
    strncpy(session, argv[1], 0x17);
    *(unsigned int *)(session + 0x1c) = 0x3e8;
    printf("Sessione %d aperta per %s\n", *(unsigned int *)(session + 0x1c), session);

    is_logout = strcmp(argv[2], "logout");
    if (is_logout == 0) {
        free(session);
        puts("Logout eseguito");
    }

    note = (char *)malloc(0x20);
    memset(note, 0, 0x20);
    strncpy(note, "promemoria", 0x17);
    if (argc < 4) {
        note_value = 0;
    } else {
        note_value = atoi(argv[3]);
    }
    *(unsigned int *)(note + 0x18) = (unsigned int)note_value;
    *(unsigned int *)(note + 0x1c) = 0x7;

    if (*(int *)(session + 0x18) == 0) {
        printf("Accesso utente per %s\n", session);
    } else {
        printf("Accesso amministratore per %s\n", session);
    }

    free(note);
    if (is_logout != 0) {
        free(session);
    }

    return 0;
}
