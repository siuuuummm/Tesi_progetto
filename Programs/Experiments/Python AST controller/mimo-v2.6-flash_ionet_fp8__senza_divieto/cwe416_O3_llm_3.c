#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int cmp_result;
    char *buf;

    if (argc < 3) {
        return 1;
    }
    setvbuf(stdout, NULL, 2, 0);
    buf = (char *)calloc(0x20, 1);
    strncpy(buf, argv[1], 0x17);
    *(int *)(buf + 0x1c) = 1000;
    printf("Sessione %d aperta per %s\n", 1000, buf);
    cmp_result = strcmp(argv[2], "logout");
    if (cmp_result == 0) {
        free(buf);
        puts("Logout eseguito");
    }
    if (argc != 3) {
        (void)strtol(argv[3], NULL, 10);
    }
    if (*(int *)(buf + 0x18) == 0) {
        printf("Accesso utente per %s\n", buf);
    }
    else {
        printf("Accesso amministratore per %s\n", buf);
    }
    if (cmp_result != 0) {
        free(buf);
    }
    return 0;
}
