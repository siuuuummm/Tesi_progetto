#include <stdio.h>

static void log_print(const char *msg)
{
    printf(msg);
    putchar(10);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    }
    else {
        printf("[log] ");
        log_print(argv[1]);
    }
    return argc < 2;
}
