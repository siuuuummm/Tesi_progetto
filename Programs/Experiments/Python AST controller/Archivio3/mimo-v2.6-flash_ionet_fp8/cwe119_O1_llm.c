#include <stdio.h>
#include <string.h>

void copy_and_print(char *param_1)
{
    char buffer[64];

    strcpy(buffer, param_1);
    printf("Buffer content: %s\n", buffer);
    return;
}

int main(void)
{
    copy_and_print(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}