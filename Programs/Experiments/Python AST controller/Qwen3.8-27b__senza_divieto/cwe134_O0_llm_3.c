#include <stdio.h>

/* Original: FUN_00400476
 * Stamps a single trailing newline after printing the argument.
 * Note: it forwards the argument directly to printf (format string taken
 * verbatim from argv), exactly as the original binary does.
 */
static void log_message(char *msg)
{
    printf(msg);
    putchar(10);
    return;
}

/* Original: FUN_004004a0 (main)
 * argv[0] = program name, argv[1] = user supplied message.
 * Returns (argc < 2): 1 when the argument is missing, 0 otherwise.
 */
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Uso: %s <messaggio>\n", "logger");
    }
    else
    {
        printf("[log] ");
        log_message(argv[1]);
    }
    return argc < 2;
}
