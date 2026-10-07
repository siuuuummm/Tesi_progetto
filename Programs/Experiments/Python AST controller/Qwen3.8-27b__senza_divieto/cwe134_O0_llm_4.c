#include <stdio.h>

/* print_message (FUN_00400476): prints the given message, then a newline. */
void print_message(const char *messaggio)
{
    printf(messaggio);
    putchar(10);
}

/* main (FUN_004004a0): usage check, then log prefix + message from argv[1]. */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
        return 1;
    }
    else {
        printf("[log] ");
        print_message(argv[1]);
        return 0;
    }
}
