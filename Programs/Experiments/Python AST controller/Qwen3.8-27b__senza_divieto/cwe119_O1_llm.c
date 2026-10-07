#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* FUN_00400476: copies the input into a 64-byte stack buffer (strcpy)
 * and prints the buffer content. */
static void print_buffer_content(const char *input)
{
    char buffer[64];

    strcpy(buffer, input);
    printf("Buffer content: %s\n", buffer);
    return;
}

/* FUN_0040049e: original main (first argument of __libc_start_main). */
int main(void)
{
    print_buffer_content(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}
