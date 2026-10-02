#include <stdio.h>
#include <string.h>

/**
 * @brief Prints the content of a buffer after copying an input string into it.
 * This function demonstrates a classic buffer overflow vulnerability (CWE-119).
 *
 * @param input The input string to be copied into the buffer.
 */
void print_buffer(char *input) {
    char buffer[64];
    
    // Vulnerable strcpy call: does not check the length of the input string
    strcpy(buffer, input);
    
    printf("Buffer content: %s\n", buffer);
}

/**
 * @brief Main logic of the program.
 * Provides a long string that exceeds the 64-byte capacity of the internal buffer.
 *
 * @return int Returns 0 upon successful execution.
 */
int main(void) {
    print_buffer("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
