#include <stdio.h>

/* FUN_00400476: prints the given message then a newline. */
void print_message(char *msg)
{
    printf(msg);
    putchar(10);
    return;
}

/* FUN_004004a0: main */
int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    }
    else {
        printf("[log] ");
        print_message(*(char **)(argv + 1));
    }
    return argc < 2;
}
