#include <stdio.h>
#include <string.h>

void print_buffer_content(char *input_string) {
    char buffer[64];
    strcpy(buffer, input_string);
    printf("Buffer content: %s\n", buffer);
}

int main(void) {
    print_buffer_content("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
