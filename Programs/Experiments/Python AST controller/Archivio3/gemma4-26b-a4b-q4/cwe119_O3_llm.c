#include <stdio.h>
#include <stdint.h>
#include <string.h>

/**
 * Reconstructed from stripped binary.
 * This program demonstrates a stack buffer overflow by copying a long string
 * into a smaller buffer using chunked moves.
 */

int main(void) {
    // The stack allocation observed in disassembly: SUB RSP, 0x48
    char stack_buf[0x48];
    
    // The constant string found at 0x4011e0
    const char *s_This_is_a_very_long_input_string = "This is a very long input string that will overflow the buffer and cause undefinfined behavior.";

    // Mimicking the stack pointer RSP as used in the disassembly
    char *rsp = stack_buf;

    // Replicating the 16-byte chunked copies using XMM registers as seen in disassembly.
    // Chunk 1: 00400394: MOVDQA XMM0, [0x4011e0]; 004003a6: MOVAPS [RSP], XMM0
    memcpy(rsp, s_This_is_a_very_long_input_string, 16);

    // Chunk 2: 004003aa: MOVDQA XMM0, [0x4011f0]; 004003b2: MOVAPS [RSP + 0x10], XMM0
    memcpy(rsp + 16, s_This_is_a_very_long_input_string + 16, 16);

    // Chunk 3: 004003b7: MOVDQA XMM0, [0x401200]; 004003bf: MOVAPS [RSP + 0x20], XMM0
    memcpy(rsp + 32, s_This_is_a_very_long_input_string + 32, 16);

    // Chunk 4: 004003c4: MOVDQA XMM0, [0x401210]; 004003cc: MOVAPS [RSP + 0x30], XMM0
    memcpy(rsp + 48, s_This_is_a_very_long_input_string + 48, 16);

    // Chunk 5: 004003d1: MOVDQA XMM0, [0x401220]; 004003d9: MOVAPS [RSP + 0x40], XMM0
    memcpy(rsp + 64, s_This_is_a_very_long_input_string + 64, 16);

    // Chunk 6: 004003de: MOVDQA XMM0, [0x401230]; 004003e6: MOVUPS [RSP + 0x4d], XMM0
    // Note: 0x4d is 77. This write causes a stack overflow as it exceeds the 0x48 (72) byte allocation.
    memcpy(rsp + 77, s_This_is_a_very_long_input_string + 80, 16);

    // 0040039c: MOV EDI, 0x4011c0 (format string: "Buffer content: %s\n");
    // 004003a3: MOV RSI, RSP (the buffer)
    printf("Buffer content: %s\n", rsp);

    return 0;
}
