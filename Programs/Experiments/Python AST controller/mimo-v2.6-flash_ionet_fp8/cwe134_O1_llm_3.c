#include <stdio.h>

/* FUN_00400476 - stampa il messaggio seguito da newline */
void print_message(char *param_1)
{
    printf(param_1);
    putchar(10);
}

/* FUN_00400493 - main */
int main(int param_1, char **param_2)
{
    if (param_1 < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    }
    else {
        printf("[log] ");
        print_message(param_2[1]);
    }
    return param_1 < 2;
}