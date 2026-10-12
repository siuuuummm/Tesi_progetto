#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* FUN_004004a0: riceve una stringa, la copia in un buffer di 72 byte sullo stack
   e ne stampa il contenuto con printf("Buffer content: %s\n", buf) */
static void copy_and_print_buffer(char *param_1)
{
    char acStack_48[72];

    strcpy(acStack_48, param_1);
    printf("Buffer content: %s\n", acStack_48);
}

/* main (FUN_00400390): chiama copy_and_print_buffer con la stringa letterale
   e restituisce 0 */
int main(void)
{
    copy_and_print_buffer(
        "This is a very long input string that will overflow the buffer "
        "and cause undefined behavior.");
    return 0;
}