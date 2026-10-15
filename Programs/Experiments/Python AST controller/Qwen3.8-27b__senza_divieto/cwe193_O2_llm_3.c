#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Ricostruzione fedele del binario stripped.
 * main decompilato a 0x004003c0 (entry -> __libc_start_main(FUN_004003c0)).
 * L'unica funzione del programma raggiungibile da entry/main e' questa;
 * FUN_00400520/FUN_00400530/FUN_00400560 sono stub di runtime (init/fini)
 * richiamati solo dalla catena di avvio, non dal main.
 */

int main(int argc, char **argv)
{
    char *s;
    char *buf;
    size_t len;
    int i;

    setvbuf(stdout, (char *)0, 2, 0);
    if (1 < argc) {
        for (i = 1; i < argc; i++) {
            s = argv[i];
            len = strlen(s);
            if (16 < len) {
                printf("Nome troppo lungo: %zu caratteri\n", len);
                continue;
            }
            buf = malloc(0x10);
            memcpy(buf, s, len + 1);
            printf("Registrato: %s (%zu caratteri)\n", buf, len);
            free(buf);
        }
    }
    return 0;
}
