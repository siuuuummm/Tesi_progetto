#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    int logout_flag;
    int is_logout;
    int note_value;
    char *user;
    char *note;

    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, NULL, 2, 0);

    user = (char *)malloc(0x20);
    memset(user, 0, 0x20);
    strncpy(user, argv[1], 0x17);
    *(uint32_t *)(user + 0x1c) = 0x3e8;
    printf("Sessione %d aperta per %s\n", *(uint32_t *)(user + 0x1c), user);

    logout_flag = strcmp(argv[2], "logout");
    is_logout = (logout_flag == 0);
    if (is_logout) {
        free(user);
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
    *(int *)(note + 0x18) = note_value;
    *(uint32_t *)(note + 0x1c) = 7;

    if (*(int *)(user + 0x18) == 0) {
        printf("Accesso utente per %s\n", user);
    } else {
        printf("Accesso amministratore per %s\n", user);
    }

    free(note);
    if (logout_flag != 0) {
        free(user);
    }

    return 0;
}
