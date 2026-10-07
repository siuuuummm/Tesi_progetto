#include <stdio.h>
#include <string.h>
#include <stdint.h>

void vulnerable_buffer_copy(char *param_1)
{
    char acStack_48[72];

    strcpy(acStack_48, param_1);
    printf("Buffer content: %s\n", acStack_48);
    return;
}

int main(void)
{
    vulnerable_buffer_copy(
        "This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}