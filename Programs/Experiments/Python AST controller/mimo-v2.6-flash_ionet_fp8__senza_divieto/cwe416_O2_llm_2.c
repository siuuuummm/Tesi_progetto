#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern long __isoc23_strtol(const char *nptr, char **endptr, int base);

int main(int argc, char **argv)
{
    char *dest;
    int cmp_result;

    if (argc < 3) {
        return 1;
    }
    setvbuf(stdout, (char *)0x0, 2, 0);
    dest = (char *)calloc(0x20, 1);
    strncpy(dest, argv[1], 0x17);
    dest[0x1c] = -0x18;
    dest[0x1d] = '\x03';
    dest[0x1e] = '\0';
    dest[0x1f] = '\0';
    printf("Sessione %d aperta per %s\n", 1000, dest);
    cmp_result = strcmp(argv[2], "logout");
    if (cmp_result == 0) {
        free(dest);
        puts("Logout eseguito");
    }
    if (argc != 3) {
        __isoc23_strtol(argv[3], 0, 10);
    }
    if (*(int *)(dest + 0x18) == 0) {
        printf("Accesso utente per %s\n", dest);
    }
    else {
        printf("Accesso amministratore per %s\n", dest);
    }
    if (cmp_result != 0) {
        free(dest);
    }
    return 0;
}
