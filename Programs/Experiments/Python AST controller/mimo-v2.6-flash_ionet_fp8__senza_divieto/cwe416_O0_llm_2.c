#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int logout_cmp;
    int note_value;
    char *user_buf;
    char *note_buf;

    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, NULL, 2, 0);

    user_buf = (char *)malloc(0x20);
    memset(user_buf, 0, 0x20);
    strncpy(user_buf, argv[1], 0x17);
    user_buf[0x1c] = -0x18;
    user_buf[0x1d] = '\x03';
    user_buf[0x1e] = '\0';
    user_buf[0x1f] = '\0';

    printf("Sessione %d aperta per %s\n", (unsigned int)*(uint32_t *)(user_buf + 0x1c), user_buf);

    logout_cmp = strcmp(argv[2], "logout");
    if (logout_cmp == 0) {
        free(user_buf);
        puts("Logout eseguito");
    }

    note_buf = (char *)malloc(0x20);
    memset(note_buf, 0, 0x20);
    strncpy(note_buf, "promemoria", 0x17);

    if (argc < 4) {
        note_value = 0;
    } else {
        note_value = atoi(argv[3]);
    }
    *(int *)(note_buf + 0x18) = note_value;
    note_buf[0x1c] = '\a';
    note_buf[0x1d] = '\0';
    note_buf[0x1e] = '\0';
    note_buf[0x1f] = '\0';

    if (*(int *)(user_buf + 0x18) == 0) {
        printf("Accesso utente per %s\n", user_buf);
    } else {
        printf("Accesso amministratore per %s\n", user_buf);
    }

    free(note_buf);

    if (logout_cmp != 0) {
        free(user_buf);
    }

    return 0;
}
