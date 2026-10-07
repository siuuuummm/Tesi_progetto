#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* FUN_004004e0: stampa una stringa seguita da newline */
void print_line(char *param_1)
{
    printf(param_1);
    putchar(10);
    return;
}

/* FUN_00400390: funzione main
   se argc < 2 stampa il messaggio d'uso, altrimenti echo del messaggio */
bool main(int param_1, long param_2)
{
    if (param_1 < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    }
    else {
        printf("[log] ");
        printf(*(char **)(param_2 + 8));
        putchar(10);
    }
    return param_1 < 2;
}