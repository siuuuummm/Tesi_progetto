#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* FUN_00400476 - copia l'input in un buffer locale di 64 byte e lo stampa */
void vulnerable_copy(char *param_1)
{
    char local_48[64];

    strcpy(local_48, param_1);
    printf("Buffer content: %s\n", local_48);
    return;
}

/* FUN_004004ae - main del programma */
int main(void)
{
    vulnerable_copy(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}