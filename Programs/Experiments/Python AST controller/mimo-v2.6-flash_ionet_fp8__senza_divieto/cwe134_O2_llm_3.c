#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    } else {
        printf("[log] ");
        printf(*(char **)(argv + 1));
        putchar(10);
    }
    return argc < 2;
}

void log_line(char *param_1)
{
    printf(param_1);
    putchar(10);
}