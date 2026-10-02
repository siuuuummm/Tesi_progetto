#include <stdio.h>
#include <string.h>

// Function that copies a string to a local buffer and prints its content
void print_buffer_content(char *input) {
    char buffer[64];
    strcpy(buffer, input);
    printf("Buffer content: %s\n", buffer);
}

// Function that demonstrates a buffer overflow vulnerability
int vulnerable_function(void) {
    print_buffer_content("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}

int main() {
    return vulnerable_function();
}