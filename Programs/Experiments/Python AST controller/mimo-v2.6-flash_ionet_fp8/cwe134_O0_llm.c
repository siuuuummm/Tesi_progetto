#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void log_message(char *param_1)
{
    printf(param_1);
    putchar(10);
    return;
}

bool main(int param_1, long param_2)
{
    if (param_1 < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    }
    else {
        printf("[log] ");
        log_message(*(char **)(param_2 + 8));
    }
    return param_1 < 2;
}