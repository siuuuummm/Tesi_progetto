#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Fedele ricostruzione del binario stripped "test_O1" (ELF x86-64, -O1).
 * Unica funzione del programma: main (FUN_004004d6 nel binario).
 *
 * I valori numerici (0x20, 0x17, 0x3e8, 0x1c, 0x18, 1000, 0xa, 2) e le
 * stringhe sono quelli letti dal decompilato / dal .rodata del binario.
 * La struttura di controllo riproduce il flusso reale, incluso il
 * use-after-free sul percorso "logout": buf viene liberato e poi ancora
 * letto/stampato, mentre la seconda free viene saltata quando il confronto
 * con "logout" e' nullo (evita double-free solo per via del flusso).
 */
int main(int argc, char **argv)
{
    int iVar1;
    char *__dest;

    iVar1 = 1;
    if (2 < argc) {
        setvbuf(stdout, (char *)0, 2, 0);
        __dest = (char *)malloc(0x20);
        memset(__dest, 0, 0x20);
        strncpy(__dest, *(char **)(argv + 1), 0x17);
        *(int *)(__dest + 0x1c) = 0x3e8;
        printf("Sessione %d aperta per %s\n", 1000, __dest);
        iVar1 = strcmp(*(char **)(argv + 2), "logout");
        if (iVar1 == 0) {
            free(__dest);
            puts("Logout eseguito");
        }
        if (3 < argc) {
            strtol(*(char **)(argv + 3), 0, 10);
        }
        if (*(int *)(__dest + 0x18) == 0) {
            printf("Accesso utente per %s\n", __dest);
        }
        else {
            printf("Accesso amministratore per %s\n", __dest);
        }
        if (iVar1 != 0) {
            free(__dest);
            iVar1 = 0;
        }
    }
    return iVar1;
}
