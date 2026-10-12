#include <stdio.h>
#include <string.h>

void vulnerable_function(char *input)
{
    char buffer[64];

    strcpy(buffer, input);
    printf("Buffer content: %s\n", buffer);
}

int main(void)
{
    char buffer[64];

    strcpy(buffer, "This is a very long input string that will overflow the buffer and cause undefined behavior.");
    printf("Buffer content: %s\n", buffer);
    return 0;
}