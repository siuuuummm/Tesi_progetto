#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* FUN_004004a0: copia la stringa in ingresso in un buffer di stack da 72 byte
 * e ne stampa il contenuto. (Buffer overflow di 21 byte: la stringa e' lunga
 * 92 caratteri + terminatore NUL = 93 byte, contro i 72 del buffer.) */
void copy_and_print(char *input)
{
    char acStack_48[72];

    strcpy(acStack_48, input);
    printf("Buffer content: %s\n", acStack_48);
    return;
}

/* main (FUN_00400390): lancia la copia/visualizzazione su una stringa molto lunga. */
int main(void)
{
    copy_and_print("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
