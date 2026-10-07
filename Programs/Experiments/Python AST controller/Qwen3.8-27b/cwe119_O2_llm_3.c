#include <stdio.h>
#include <string.h>

/* FUN_004004a0
 * Copies the input string into a 72-byte stack buffer (overflow)
 * and prints the buffer content.
 */
void print_buffer(char *param_1)
{
    char acStack_48[72];

    strcpy(acStack_48, param_1);
    printf("Buffer content: %s\n", acStack_48);
    return;
}

/* FUN_00400390 (main)
 * Entry point resolved from __libc_start_main.
 * Feeds a long fixed input string to print_buffer.
 */
int main(void)
{
    print_buffer("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
