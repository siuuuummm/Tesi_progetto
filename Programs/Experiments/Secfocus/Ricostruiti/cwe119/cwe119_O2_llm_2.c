#include <stdio.h>
#include <string.h>

// Function that triggers the buffer overflow
void vulnerable_function(char *input) {
    char buffer[72];
    strcpy(buffer, input);  // Unsafe copy - buffer overflow if input > 71 chars
    printf("Buffer content: %s\n", buffer);
}

int main(void) {
    // This is what gets called first in program logic
    vulnerable_function("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
