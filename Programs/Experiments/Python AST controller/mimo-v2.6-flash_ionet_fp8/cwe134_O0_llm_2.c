#include <stdio.h>
#include <stdint.h>

/* FUN_00400476: stampa il messaggio come formato printf e a capo */
void stampa_messaggio(char *param_1)
{
    printf(param_1);
    putchar(10);
    return;
}

/* FUN_004004a0: main */
int main(int param_1, long param_2)
{
    if (param_1 < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    }
    else {
        printf("[log] ");
        stampa_messaggio(*(char **)(param_2 + 8));
    }
    return param_1 < 2;
}