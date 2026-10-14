#include <stdio.h>
#include <string.h>

int main() {
    char buffer[72];
    strcpy(buffer, "This is a very long input string that will overflow the buffer and cause undefinfined behavior.");
    printf("Buffer content: %s\n", buffer);
    return 0;
}
