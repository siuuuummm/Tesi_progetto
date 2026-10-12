#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int r;
    char *dest;

    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, (char *)0, 2, 0);
    dest = (char *)calloc(0x20, 1);
    strncpy(dest, argv[1], 0x17);
    *(int *)(dest + 0x1c) = 0x3e8;
    printf("Sessione %d aperta per %s\n", 1000, dest);
    r = strcmp(argv[2], "logout");
    if (r == 0) {
        free(dest);
        puts("Logout eseguito");
    }
    if (argc != 3) {
        strtol(argv[3], (char **)0, 10);
    }
    if (*(int *)(dest + 0x18) == 0) {
        printf("Accesso utente per %s\n", dest);
    }
    else {
        printf("Accesso amministratore per %s\n", dest);
    }
    if (r != 0) {
        free(dest);
    }
    return 0;
}
