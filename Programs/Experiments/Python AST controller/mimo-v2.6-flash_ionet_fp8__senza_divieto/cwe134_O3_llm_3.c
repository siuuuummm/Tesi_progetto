extern int printf(const char *format, ...);
extern int putchar(int c);

void log_message(const char *message)
{
    printf(message);
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