#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void print_line(char *msg)
{
    printf(msg);
    putchar(10);
    return;
}

bool main(int argc, long argv)
{
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    }
    else {
        printf("[log] ");
        print_line(*(char **)(argv + 8));
    }
    return argc < 2;
}