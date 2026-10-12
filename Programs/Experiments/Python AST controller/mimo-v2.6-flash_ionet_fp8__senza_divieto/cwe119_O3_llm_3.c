#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* .rodata @0x4011e0: 95 caratteri + '\0' = 96 byte (0x60) */
static const char s_This_is_a_very_long_input_string_004011e0[] =
    "This is a very long input string that will overflow the buffer "
    "and cause undefinfined behavior.";

/* .rodata @0x4011c0 */
#define FORMAT_STRING "Buffer content: %s\n"

/*
 * FUN_004004f0 (0x004004f0):
 *   sub  rsp,0x48
 *   mov  rsi,rdi
 *   mov  rdi,rsp
 *   call strcpy@plt
 *   mov  rsi,rsp
 *   mov  edi,0x4011c0
 *   xor  eax,eax
 *   call printf@plt
 *   add  rsp,0x48
 *   ret
 */
void copy_and_print(char *param_1)
{
    char acStack_48[72];            /* frame da 0x48 byte */

    strcpy(acStack_48, param_1);
    printf(FORMAT_STRING, acStack_48);
}

/*
 * FUN_00400390 = main (primo argomento di __libc_start_main in entry)
 *
 * sub rsp,0x48
 * movdqa/movaps da 0x4011e0..0x40122f in [rsp+0x00 .. rsp+0x4f]
 * movups da 0x401230 in [rsp+0x4d]   (byte 80..95 della stringa)
 * mov edi,0x4011c0 ; xor eax,eax ; mov rsi,rsp ; call printf@plt
 * xor eax,eax ; add rsp,0x48 ; ret
 */
int main(void)
{
    char local_48[72];              /* frame da 0x48 byte */

    /* copia dei 96 byte della costante sullo stack (xmm store sovrapposti:
       offset 0x00,0x10,0x20,0x30,0x40 e infine 0x4d) */
    memcpy(local_48, s_This_is_a_very_long_input_string_004011e0, 0x60);

    printf(FORMAT_STRING, local_48);
    return 0;
}