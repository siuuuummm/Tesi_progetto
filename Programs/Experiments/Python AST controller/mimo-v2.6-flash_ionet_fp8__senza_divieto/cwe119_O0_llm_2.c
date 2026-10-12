#include <stdio.h>
#include <string.h>
#include <stdint.h>

static void print_buffer_copy(char *param_1)
{
    char local_48[64];

    strcpy(local_48, param_1);
    printf("Buffer content: %s\n", local_48);
    return;
}

int main(void)
{
    print_buffer_copy(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}