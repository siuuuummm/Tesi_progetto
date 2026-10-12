#include <stdio.h>
#include <string.h>

void copy_and_print_buffer(char *param_1)
{
    char local_48[64];

    strcpy(local_48, param_1);
    printf("Buffer content: %s\n", local_48);
    return;
}

int main(void)
{
    copy_and_print_buffer(
        "This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}