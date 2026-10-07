#include <stdio.h>
#include <string.h>

/*
 * Reconstructed from the stripped binary test_O1 (compiled with -O1).
 *
 * Original function at 0x00400476:
 *   push  %rbx
 *   sub   $0x40,%rsp            ; 64-byte stack buffer (0x40 bytes)
 *   mov   %rdi,%rsi             ; rsi = input (source)
 *   mov   %rsp,%rdi             ; rdi = buffer (destination)
 *   call  strcpy@plt            ; strcpy(buffer, input)
 *   mov   %rsp,%rsi             ; rsi = buffer
 *   mov   $0x4011c0,%edi        ; edi = "Buffer content: %s\n"
 *   mov   $0x0,%eax             ; no varargs
 *   call  printf@plt            ; printf("Buffer content: %s\n", buffer)
 *   add   $0x40,%rsp
 *   pop   %rbx
 *   ret
 *
 * Takes a string, copies it into a fixed-size 64-byte stack buffer via
 * strcpy (no bounds checking), then prints the buffer. This is the
 * classic buffer-overflow sink the program is built to demonstrate.
 */
void vulnerable(char *input)
{
    char acStack_48[64];

    strcpy(acStack_48, input);
    printf("Buffer content: %s\n", acStack_48);
}

/*
 * Original main at 0x0040049e:
 *   sub   $0x8,%rsp
 *   mov   $0x4011d8,%edi        ; "This is a very long input string ..."
 *   call  0x00400476            ; vulnerable(long_string)
 *   mov   $0x0,%eax             ; return 0
 *   add   $0x8,%rsp
 *   ret
 *
 * Calls vulnerable() with a literal string that is far longer than the
 * 64-byte destination buffer, triggering a stack buffer overflow.
 * Returns 0.
 */
int main(void)
{
    vulnerable(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}
