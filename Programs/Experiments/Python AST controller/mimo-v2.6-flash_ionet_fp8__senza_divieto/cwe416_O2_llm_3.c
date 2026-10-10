#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *name;
    int cmp;

    if (argc < 3) {
        return 1;
    }
    setvbuf(stdout, NULL, 2, 0);
    name = (char *)calloc(0x20, 1);
    strncpy(name, argv[1], 0x17);
    name[0x1c] = (char)-0x18;
    name[0x1d] = '\x03';
    name[0x1e] = '\0';
    name[0x1f] = '\0';
    printf("Sessione %d aperta per %s\n", 1000, name);
    cmp = strcmp(argv[2], "logout");
    if (cmp == 0) {
        free(name);
        puts("Logout eseguito");
    }
    if (argc != 3) {
        strtol(argv[3], NULL, 10);
    }
    if (*(int *)(name + 0x18) == 0) {
        printf("Accesso utente per %s\n", name);
    } else {
        printf("Accesso amministratore per %s\n", name);
    }
    if (cmp != 0) {
        free(name);
    }
    return 0;
}