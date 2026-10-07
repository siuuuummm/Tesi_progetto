#include <stdio.h>
#include <string.h>

void vulnerable_copy_and_print(char *param_1)
{
    char acStack_48[64];

    strcpy(acStack_48, param_1);
    printf("Buffer content: %s\n", acStack_48);
    return;
}

int main(void)
{
    vulnerable_copy_and_print(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}