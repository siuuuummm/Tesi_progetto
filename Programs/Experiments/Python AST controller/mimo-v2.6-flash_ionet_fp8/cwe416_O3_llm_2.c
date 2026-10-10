#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern long int __isoc23_strtol(const char *nptr, char **endptr, int base);

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
    *(int32_t *)(dest + 0x1c) = 1000;
    printf("Sessione %d aperta per %s\n", 1000, dest);
    cmp_result = strcmp(argv[2], "logout");
    if (cmp_result == 0) {
        free(dest);
        puts("Logout eseguito");
    }
    if (argc != 3) {
        __isoc23_strtol(argv[3], NULL, 10);
    }
    if (*(int32_t *)(dest + 0x18) == 0) {
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
