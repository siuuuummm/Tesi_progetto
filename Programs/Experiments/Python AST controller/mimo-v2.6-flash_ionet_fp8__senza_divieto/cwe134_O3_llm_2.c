#include <stdio.h>

int main(int param_1, char **param_2)
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