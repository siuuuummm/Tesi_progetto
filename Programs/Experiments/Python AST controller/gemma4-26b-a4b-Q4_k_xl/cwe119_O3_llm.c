#include <stdio.h>
#include <string.h>
#include <stdint.h>

void vulnerable_function(char *param_1) {
    char acStack_48[72];
    strcpy(acStack_48, param_1);
    printf("Buffer content: %s\n", acStack_48);
}

int main() {
    char buffer[72];
    strcpy(buffer, "This is a very long input string that will overflow the buffer and cause undefinfined behavior.");
    printf("Buffer content: %s\n", buffer);
    return 0;
}
