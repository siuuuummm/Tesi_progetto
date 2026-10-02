/* cwe416.c — CWE-416: Use After Free.
 * Dopo il logout la sessione viene liberata ma il puntatore resta in uso.
 * La nota allocata subito dopo riusa lo stesso blocco: priority finisce in
 * is_admin, quindi "mario logout 1" ottiene l'accesso amministratore. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[24];
    int is_admin;
    int id;
} Session;

typedef struct {
    char text[24];
    int priority;
    int flags;
} Note;

int main(int argc, char *argv[]) {
    if (argc < 3)
        return 1;
    setvbuf(stdout, NULL, _IONBF, 0);

    Session *s = malloc(sizeof(Session));
    memset(s, 0, sizeof(Session));
    strncpy(s->name, argv[1], sizeof(s->name) - 1);
    s->id = 1000;
    printf("Sessione %d aperta per %s\n", s->id, s->name);

    int logout = strcmp(argv[2], "logout") == 0;
    if (logout) {
        free(s);                 /* vulnerabile: s non viene azzerato */
        printf("Logout eseguito\n");
    }

    Note *n = malloc(sizeof(Note));
    memset(n, 0, sizeof(Note));
    strncpy(n->text, "promemoria", sizeof(n->text) - 1);
    n->priority = argc > 3 ? atoi(argv[3]) : 0;
    n->flags = 7;

    if (s->is_admin)
        printf("Accesso amministratore per %s\n", s->name);
    else
        printf("Accesso utente per %s\n", s->name);

    free(n);
    if (!logout)
        free(s);
    return 0;
}
