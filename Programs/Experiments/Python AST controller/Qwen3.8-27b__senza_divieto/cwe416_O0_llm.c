#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    int confronto;
    int val;
    char *sessione;
    char *nota;

    if (argc < 3) {
        return 1;
    }

    setvbuf(stdout, NULL, 2, 0);

    sessione = (char *)malloc(0x20);
    memset(sessione, 0, 0x20);
    strncpy(sessione, argv[1], 0x17);
    *(int *)(sessione + 0x1c) = 0x3e8;
    printf("Sessione %d aperta per %s\n", *(int *)(sessione + 0x1c), sessione);

    confronto = strcmp(argv[2], "logout");
    if (confronto == 0) {
        free(sessione);
        puts("Logout eseguito");
    }

    nota = (char *)malloc(0x20);
    memset(nota, 0, 0x20);
    strncpy(nota, "promemoria", 0x17);
    if (argc < 4) {
        val = 0;
    }
    else {
        val = atoi(argv[3]);
    }
    *(int *)(nota + 0x18) = val;
    *(int *)(nota + 0x1c) = 7;

    if (*(int *)(sessione + 0x18) == 0) {
        printf("Accesso utente per %s\n", sessione);
    }
    else {
        printf("Accesso amministratore per %s\n", sessione);
    }

    free(nota);
    if (confronto != 0) {
        free(sessione);
    }

    return 0;
}
