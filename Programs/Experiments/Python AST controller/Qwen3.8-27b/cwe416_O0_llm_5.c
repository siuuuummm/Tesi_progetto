#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/*
 * Ricompilazione fedele del binario stripped test_O0 (x86-64, -O0).
 *
 * La funzione principale corrisponde a FUN_004004e6. I puntatori al
 * rodata vengono mappati sulle esatte stringhe presenti in .rodata:
 *   0x401390: "Sessione %d aperta per %s\n"
 *   0x4013ab: "logout"
 *   0x4013b2: "Logout eseguito"
 *   0x4013c2: "promemoria"
 *   0x4013d0: "Accesso amministratore per %s\n"
 *   0x4013ef: "Accesso utente per %s\n"
 *
 * Ogni costante (0x20, 0x17, 0x1c, 0x18, 0x3e8, 0x7) e la struttura di
 * controllo sono riprodotte esattamente come nel decompilato, senza
 * correzioni: il blocco di 32 byte (0x20) contiene un campo char da
 * 0x1c byte (28) seguito da un int a offset 0x1c.
 */

typedef struct {
    char name[0x1c];  /* 28 byte: 0x00 .. 0x1b */
    int  id;          /* 4 byte  : 0x1c .. 0x1f */
} user_t;             /* sizeof = 0x20 = 32 */

int main(int param_1, char **param_2)
{
    char *dest;
    char *dest_0;
    int is_logout;

    if (param_1 < 3) {
        return 1;
    }

    setvbuf(stdout, (char *)0x0, 2, 0);

    /* param_2 e' argv. I decompilati usano OFFSET IN BYTE (param_2 e' tipizzato
       come long): +8  -> argv[1], +0x10 -> argv[2], +0x18 -> argv[3].
       Cast a (char *) per riprodurre fedelmente gli offset numerici 8/0x10/0x18. */

    /* malloc(0x20); memset(0, 0x20); strncpy(dest, argv[1], 0x17);
       *(int *)(dest + 0x1c) = 0x3e8;                              */
    dest = (char *)malloc(0x20);
    memset(dest, 0x0, 0x20);
    strncpy(dest, *(char **)((char *)param_2 + 8), 0x17);
    *(int *)(dest + 0x1c) = 0x3e8;   /* 1000 */

    printf("Sessione %d aperta per %s\n", *(unsigned int *)(dest + 0x1c), dest);

    /* if (strcmp(argv[2], "logout") == 0) { free(dest); puts("Logout eseguito"); } */
    is_logout = (strcmp(*(char **)((char *)param_2 + 0x10), "logout") == 0);
    if (is_logout) {
        free(dest);
        puts("Logout eseguito");
    }

    /* malloc(0x20); memset(0, 0x20); strncpy(dest_0, "promemoria", 0x17);
       *(int *)(dest_0 + 0x18) = (argc < 4) ? 0 : atoi(argv[3]);
       *(int *)(dest_0 + 0x1c) = 0x7;                               */
    dest_0 = (char *)malloc(0x20);
    memset(dest_0, 0x0, 0x20);
    strncpy(dest_0, "promemoria", 0x17);

    if (param_1 < 4) {
        *(int *)(dest_0 + 0x18) = 0;
    }
    else {
        *(int *)(dest_0 + 0x18) = atoi(*(char **)((char *)param_2 + 0x18));
    }

    *(int *)(dest_0 + 0x1c) = 0x7;   /* 7 */

    /* if (*(int *)(dest + 0x18) == 0) -> utente, else -> amministratore */
    if (*(int *)(dest + 0x18) == 0) {
        printf("Accesso utente per %s\n", dest);
    }
    else {
        printf("Accesso amministratore per %s\n", dest);
    }

    free(dest_0);

    /* se NON era logout: libera anche il primo buffer */
    if (!is_logout) {
        free(dest);
    }

    return 0;
}
