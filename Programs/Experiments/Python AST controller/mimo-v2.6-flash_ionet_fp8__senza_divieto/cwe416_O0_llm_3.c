#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int is_logout;
    int memo_value;
    char *user_buf;
    char *memo_buf;

    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, NULL, 2, 0);

    user_buf = (char *)malloc(0x20);
    memset(user_buf, 0, 0x20);
    strncpy(user_buf, argv[1], 0x17);
    *(uint32_t *)(user_buf + 0x1c) = 0x3e8;

    printf("Sessione %d aperta per %s\n", *(uint32_t *)(user_buf + 0x1c), user_buf);

    is_logout = (strcmp(argv[2], "logout") == 0);
    if (is_logout) {
        free(user_buf);
        puts("Logout eseguito");
    }

    memo_buf = (char *)malloc(0x20);
    memset(memo_buf, 0, 0x20);
    strncpy(memo_buf, "promemoria", 0x17);
    if (argc < 4) {
        memo_value = 0;
    } else {
        memo_value = atoi(argv[3]);
    }
    *(int *)(memo_buf + 0x18) = memo_value;
    *(int *)(memo_buf + 0x1c) = 7;

    if (*(int *)(user_buf + 0x18) == 0) {
        printf("Accesso utente per %s\n", user_buf);
    } else {
        printf("Accesso amministratore per %s\n", user_buf);
    }

    free(memo_buf);
    if (!is_logout) {
        free(user_buf);
    }

    return 0;
}
