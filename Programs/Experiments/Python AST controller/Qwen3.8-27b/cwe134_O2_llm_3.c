#include <stdio.h>

/* FUN_004004e0: stampa il messaggio seguito da un newline (format string diretta) */
void log_message(char *msg)
{
    printf(msg);
    putchar(10);
}

/* FUN_00400390: main del "logger" */
int main(int argc, char *argv[])
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
