#include <stdio.h>
#include <stdint.h>

/* FUN_00400476: stampa il messaggio (come stringa di formato) seguito da un newline. */
static void log_message(char *msg)
{
    printf(msg);
    putchar(10);
}

/* FUN_004004a0 (main) */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    }
    else {
        printf("[log] ");
        log_message(argv[1]);
    }
    return argc < 2;
}
