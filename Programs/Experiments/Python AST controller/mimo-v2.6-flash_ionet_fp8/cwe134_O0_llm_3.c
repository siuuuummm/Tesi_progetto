#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void print_message_line(char *message)
{
    printf(message);
    putchar(10);
}

int main(int argc, long argv)
{
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    }
    else {
        printf("[log] ");
        print_message_line(*(char **)(argv + 8));
    }
    return argc < 2;
}