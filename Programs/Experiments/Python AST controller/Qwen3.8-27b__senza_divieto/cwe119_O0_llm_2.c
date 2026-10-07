#include <stdio.h>
#include <string.h>

/*
 * FUN_00400476
 *
 * Copies `input` into a fixed-size 64-byte stack buffer using the unbounded
 * strcpy() and then prints the buffer contents. Because strcpy() performs no
 * bounds checking, a source longer than the buffer overflows it.
 */
void overflow_buffer(char *input)
{
    char buffer[64];

    strcpy(buffer, input);
    printf("Buffer content: %s\n", buffer);
    return;
}

int main(void)
{
    overflow_buffer(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}
