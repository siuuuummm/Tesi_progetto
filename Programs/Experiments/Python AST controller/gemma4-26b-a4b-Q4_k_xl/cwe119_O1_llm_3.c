#include <stdio.h>
#include <string.h>

void vuln(char *input) {
    char buffer[64];
    strcpy(buffer, input);
    printf("Buffer content: %s\n", buffer);
}

int main(void) {
    vuln("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
