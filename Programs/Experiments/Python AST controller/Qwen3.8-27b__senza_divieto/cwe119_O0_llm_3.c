#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Decompilato da FUN_00400476.
 * Copia l'input in un buffer fisso da 64 byte (strcpy) e lo stampa. */
void overflow_buffer(char *param_1)
{
    char buffer[64];

    strcpy(buffer, param_1);
    printf("Buffer content: %s\n", buffer);
    return;
}

/* Decompilato da FUN_004004ae (main). */
int main(void)
{
    overflow_buffer(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}
