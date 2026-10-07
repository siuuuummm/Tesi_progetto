#include <stdio.h>
#include <string.h>

/*
 * FUN_004004a0 (0x4004a0):
 *   SUB RSP,0x48 ; 72-byte stack buffer
 *   MOV RSI,RDI  ; rsi = input
 *   MOV RDI,RSP  ; rdi = buffer
 *   CALL strcpy
 *   MOV RSI,RSP  ; rsi = buffer
 *   MOV EDI,0x4011c0 ; "Buffer content: %s\n"
 *   XOR EAX,EAX
 *   CALL printf
 *   ADD RSP,0x48
 *   RET
 */
void process_buffer(char *input)
{
    char buf[72];

    strcpy(buf, input);
    printf("Buffer content: %s\n", buf);
    return;
}

/*
 * main (0x400390):
 *   SUB RSP,0x8
 *   MOV EDI,0x4011d8 ; the long literal
 *   CALL process_buffer
 *   XOR EAX,EAX ; return 0
 *   ADD RSP,0x8
 *   RET
 */
int main(void)
{
    process_buffer("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
