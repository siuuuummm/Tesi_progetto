#include <stdio.h>

void log_message(char *msg)
{
    printf(msg);
    putchar('\n');
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
        return 1;
    }
    printf("[log] ");
    log_message(argv[1]);
    return 0;
}
