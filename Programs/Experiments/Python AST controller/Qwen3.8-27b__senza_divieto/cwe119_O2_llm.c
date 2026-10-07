#include <stdio.h>
#include <string.h>

void process_buffer(char *input)
{
    char acStack_48[72];

    strcpy(acStack_48, input);
    printf("Buffer content: %s\n", acStack_48);
    return;
}

int main(void)
{
    process_buffer(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}
