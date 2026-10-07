#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void print_message_line(char *param_1)
{
    printf(param_1);
    putchar(10);
    return;
}

bool main_logger(int param_1, long param_2)
{
    if (param_1 < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    } else {
        printf("[log] ");
        print_message_line(*(char **)(param_2 + 8));
    }
    return param_1 < 2;
}

int main(int argc, char **argv)
{
    return (int)main_logger(argc, (long)argv);
}