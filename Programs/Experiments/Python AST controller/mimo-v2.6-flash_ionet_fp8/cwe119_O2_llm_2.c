#include <stdio.h>
#include <string.h>
#include <stdint.h>

void overflow_buffer(char *param_1)
{
    char acStack_48[72];

    strcpy(acStack_48, param_1);
    printf("Buffer content: %s\n", acStack_48);
    return;
}

int main(void)
{
    overflow_buffer(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}