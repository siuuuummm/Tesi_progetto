#include <stdio.h>
#include <string.h>

/*
 * Corresponds to FUN_00400476 in the binary.
 * Copies the input string into a 64-byte stack buffer and prints it.
 * The buffer is allocated with `SUB RSP, 0x40` (64 bytes) at 0x00400477.
 */
void print_buffer(const char *input)
{
    char buffer[64];

    strcpy(buffer, input);
    printf("Buffer content: %s\n", buffer);
}

/*
 * Corresponds to main (FUN_0040049e) in the binary.
 * Passes the long literal string (stored at 0x4011d8) to print_buffer,
 * which overflows the 64-byte buffer.
 */
int main(void)
{
    print_buffer(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}
