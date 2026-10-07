#include <stdio.h>
#include <string.h>

/* Original FUN_00400476: copies the input string into a 64-byte stack
 * buffer with strcpy (the input is 92 chars + NUL, so this overflows),
 * then prints the buffer content. */
void copy_and_print(char *input)
{
    char acStack_48[64];

    strcpy(acStack_48, input);
    printf("Buffer content: %s\n", acStack_48);
    return;
}

/* Original FUN_0040049e: passes a fixed long literal to copy_and_print,
 * then returns 0. */
int main(void)
{
    copy_and_print("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
