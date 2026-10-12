#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* FUN_00400476: copia la stringa in un buffer locale da 64 byte e la stampa */
void copy_and_print_buffer(char *param_1)
{
    char local_48[64];

    strcpy(local_48, param_1);
    printf("Buffer content: %s\n", local_48);
    return;
}

/* FUN_004004ae: main - passa la stringa di input a copy_and_print_buffer */
int main(void)
{
    copy_and_print_buffer(
        "This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}