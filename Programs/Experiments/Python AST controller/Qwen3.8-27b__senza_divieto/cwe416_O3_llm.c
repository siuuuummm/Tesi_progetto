#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static void __attribute__((noinline)) noop1(void)
{
    return;
}

static void __attribute__((noinline)) noop2(void)
{
    return;
}

static void __attribute__((noinline)) noop3(void)
{
    return;
}

int main(int argc, char **argv)
{
    char *dest;

    if (argc < 3)
        return 0;

    setvbuf(stdout, (char *)0, 2, 0);
    dest = (char *)calloc(0x20, 1);
    strncpy(dest, argv[1], 0x17);
    dest[0x1c] = (char)0xe8;
    dest[0x1d] = '\x03';
    dest[0x1e] = '\0';
    dest[0x1f] = '\0';
    printf("Sessione %d aperta per %s\n", 1000, dest);
    if (strcmp(argv[2], "logout") == 0) {
        free(dest);
        puts("Logout eseguito");
    }
    if (argc != 3) {
        (void)strtol(argv[3], 0, 10);
    }
    if (*(int *)(dest + 0x18) == 0) {
        printf("Accesso utente per %s\n", dest);
    }
    else {
        printf("Accesso amministratore per %s\n", dest);
    }
    if (strcmp(argv[2], "logout") != 0) {
        free(dest);
    }
    return 0;
}
