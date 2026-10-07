#include <stdio.h>
#include <string.h>

void vulnerable_function(char *input) {
    char buffer[64];
    strcpy(buffer, input);
    printf("Buffer content: %s\n", buffer);
}

int main(void) {
    vulnerable_function("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
