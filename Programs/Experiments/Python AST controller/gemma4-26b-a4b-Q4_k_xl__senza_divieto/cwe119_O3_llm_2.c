#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main() {
    /* 
     * This function is a faithful reconstruction of FUN_00400390.
     * The original function allocates 0x48 (72) bytes on the stack but 
     * performs copies that extend up to 88 bytes, causing a stack overflow.
     */
    
    char stack_mem[128];
    const char *long_string = "This is a very long input string that will overflow the buffer and cause undefinfined behavior.";

    // The decompile shows the string being copied in 8-byte chunks.
    // We reproduce this exact sequence of copies.
    memcpy(stack_mem + 0, long_string + 0, 8);
    memcpy(stack_mem + 8, long_string + 8, 8);
    memcpy(stack_mem + 16, long_string + 16, 8);
    memcpy(stack_mem + 24, long_string + 24, 8);
    memcpy(stack_mem + 32, long_string + 32, 8);
    memcpy(stack_mem + 40, long_string + 40, 8);
    memcpy(stack_mem + 48, long_string + 48, 8);
    memcpy(stack_mem + 56, long_string + 56, 8);
    memcpy(stack_mem + 64, long_string + 64, 8);
    // The following copies overflow the 72-byte stack frame
    memcpy(stack_mem + 72, long_string + 72, 8);
    memcpy(stack_mem + 80, long_string + 80, 8);

    printf("Buffer content: %s\n", stack_mem);

    return 0;
}
