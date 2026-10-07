#include <stdio.h>
#include <string.h>

/* FUN_004004a0: copies an input string into a fixed-size 72-byte stack
 * buffer with an unbounded strcpy (buffer overflow) and prints the result. */
void copy_and_print(char *input)
{
    char acStack_48[72];

    strcpy(acStack_48, input);
    printf("Buffer content: %s\n", acStack_48);
    return;
}

/* FUN_00400390: main */
int main(void)
{
    copy_and_print(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}
