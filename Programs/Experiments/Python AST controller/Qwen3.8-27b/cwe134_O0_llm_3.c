#include <stdio.h>
#include <stdint.h>

/*
 * FUN_00400476
 * Funzione di logging: emette il messaggio usando printf con il
 * messaggio stesso come stringa di formato, poi scrive un newline.
 */
static void log_message(const char *msg)
{
    printf(msg);
    putchar(10);
    return;
}

/*
 * FUN_004004a0 (main)
 * Se argc < 2 stampa l'uso, altrimenti stampe il prefisso "[log] "
 * e invia argv[1] alla funzione di logging. Restituisce argc < 2.
 */
int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    }
    else {
        printf("[log] ");
        log_message(argv[1]);
    }
    return argc < 2;
}
