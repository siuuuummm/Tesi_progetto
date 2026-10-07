#include <stdio.h>

/* Stampa un messaggio di log: printf(param) + a capo (FUN_004004e0) */
void log_line(char *msg)
{
    printf(msg);
    putchar(10);
    return;
}

/* main (FUN_00400390): logger con argomento */
int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    }
    else {
        printf("[log] ");
        printf(argv[1]);
        putchar(10);
    }
    return argc < 2;
}