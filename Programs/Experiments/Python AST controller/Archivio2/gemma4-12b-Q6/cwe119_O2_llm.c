#include <stdio.h>
#include <string.h>

/**
 * @brief Prints a buffer to stdout after copying the input string into it.
 * This function is vulnerable to a buffer overflow because it uses strcpy
 * without checking the length of the input string.
 *
 * @param input The input string to be copied into the buffer.
 */
void print_buffer(char *input) {
    char buffer[72];
    strcpy(buffer, input);
    printf("Buffer content: %s\n", buffer);
}

/**
 * @brief Main entry point of the program.
 * Demonstrates a buffer overflow by calling print_buffer with a string
 * that exceeds the internal buffer size.
 *
 * @return int Execution status.
 */
int main(void) {
    print_buffer("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
