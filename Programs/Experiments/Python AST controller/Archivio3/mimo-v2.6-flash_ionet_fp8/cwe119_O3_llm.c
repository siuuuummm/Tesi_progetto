#include <stdio.h>
#include <string.h>

int main(void)
{
    static const char input_string[0x60] =
        "This is a very long input string that will overflow the buffer and cause undefinfined behavior.";
    char buffer[0x48];

    memcpy(buffer + 0x00, input_string + 0x00, 0x10);
    memcpy(buffer + 0x10, input_string + 0x10, 0x10);
    memcpy(buffer + 0x20, input_string + 0x20, 0x10);
    memcpy(buffer + 0x30, input_string + 0x30, 0x10);
    memcpy(buffer + 0x40, input_string + 0x40, 0x10);
    memcpy(buffer + 0x4d, input_string + 0x50, 0x10);

    printf("Buffer content: %s\n", buffer);
    return 0;
}