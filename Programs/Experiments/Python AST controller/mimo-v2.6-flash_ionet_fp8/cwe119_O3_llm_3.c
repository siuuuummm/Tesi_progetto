#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*
 * Funzione print_and_return_zero (FUN_00400390 - main):
 * Il binario esegue: sub rsp,0x48 -> buffer locale di 72 byte sullo stack.
 * La stringa sorgente (92 caratteri + '\0' = 93 byte) viene copiata nel
 * buffer con movdqa/movaps (6 x 16 byte da 0x4011e0) e infine movups di
 * 16 byte a [rsp+0x4d] (offset 77), cioe' la stessa inlining di strcpy
 * prodotta da gcc -O3: la scrittura finisce a offset 77+16 = 93, quindi
 * oltre i 72 byte del buffer (overflow di 21 byte).
 */
int main(void)
{
    char buffer[72];

    strcpy(buffer,
           "This is a very long input string that will overflow the buffer and cause undefinfined behavior.");

    printf("Buffer content: %s\n", buffer);
    return 0;
}

/*
 * Funzione unsafe_copy_and_print (FUN_004004f0):
 * decompilata da 0x004004f0:
 *   void FUN_004004f0(char *param_1)
 *   {
 *     char acStack_48 [72];
 *     strcpy(acStack_48, param_1);
 *     printf("Buffer content: %s\n", acStack_48);
 *     return;
 *   }
 * Il buffer sullo stack e' di 0x48 = 72 byte (sub rsp,0x48 nel binario).
 */
void unsafe_copy_and_print(char *param_1)
{
    char acStack_48[72];

    strcpy(acStack_48, param_1);
    printf("Buffer content: %s\n", acStack_48);
    return;
}