#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

void print_buffer_content(char *param_1)
{
    char buffer[72];

    strcpy(buffer, param_1);
    printf("Buffer content: %s\n", buffer);
    return;
}

int main(void)
{
    print_buffer_content(
        "This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}