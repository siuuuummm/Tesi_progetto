#include <stdio.h>

/* Reconstructed from stripped binary.
 * FUN_00400476 -> print_message
 */
void print_message(char *param_1)
{
    printf(param_1);
    putchar(10);
    return;
}

/* main -> FUN_004004a0 */
int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    }
    else {
        printf("[log] ");
        print_message(argv[1]);
    }
    return argc < 2;
}
