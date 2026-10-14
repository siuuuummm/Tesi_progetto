#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*
 * Reconstructed C code from a stripped binary.
 * The program demonstrates a stack-based buffer overflow.
 */

int main(void) {
    /* The input string located at 0x4011e0 */
    const char *input_string = "This_is_a_very_long_input_string_This_is_a_very_long_input_string_This_is_a_very_long_input_string_";

    /* Stack allocation: SUB RSP, 0x48 */
    uint8_t buffer[72];

    /* 
     * The following sequence of moves replicates the assembly logic:
     * 0x400394: MOVDQA XMM0, [0x4011e0]; 0x4003a6: MOVAPS [RSP], XMM0
     * 0x4003aa: MOVDQA XMM0, [0x4011f0]; 0x4003b2: MOVAPS [RSP + 0x10], XMM0
     * 0x4003b7: MOVDQA XMM0, [0x401200]; 0x4003bf: MOVAPS [RSP + 0x20], XMM0
     * 0x4003c4: MOVDQA XMM0, [0x401210]; 0x4003cc: MOVAPS [RSP + 0x30], XMM0
     * 0x4003d1: MOVDQA XMM0, [0x401220]; 0x4003d9: MOVAPS [RSP + 0x40], XMM0
     * 0x4003de: MOVDQA XMM0, [0x401230]; 0x4003e6: MOVUPS [RSP + 0x4d], XMM0
     */

    memcpy(buffer + 0, input_string + 0, 16);
    memcpy(buffer + 16, input_string + 16, 16);
    memcpy(buffer + 32, input_string + 32, 16);
    memcpy(buffer + 48, input_string + 48, 16);
    memcpy(buffer + 64, input_string + 64, 16);
    // Note the unaligned and overlapping copy at RSP + 0x4d (77)
    memcpy(buffer + 77, input_string + 77, 16);

    /* Print the buffer content */
    printf("Buffer content: %s\n", buffer);

    return 0;
}
