#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc <= 2) {
        return 1;
    }

    setvbuf(stdout, (char *)0, 2, 0);

    char *name = (char *)calloc(0x20, 1);
    strncpy(name, argv[1], 0x17);
    *(int *)(name + 0x1c) = 0x3e8;

    printf("Sessione %d aperta per %s\n", 1000, name);

    int cmp = strcmp(argv[2], "logout");
    if (cmp == 0) {
        free(name);
        puts("Logout eseguito");
    }

    if (argc != 3) {
        strtol(argv[3], (char **)0, 10);
    }

    if (*(int *)(name + 0x18) == 0) {
        printf("Accesso utente per %s\n", name);
    }
    else {
        printf("Accesso amministratore per %s\n", name);
    }

    if (cmp != 0) {
        free(name);
    }

    return 0;
}
