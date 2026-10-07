#include <stdio.h>
#include <string.h>

/* Copies an arbitrary string into a fixed 72-byte stack buffer using
 * strcpy (no bounds checking) and prints the buffer back out. */
void print_buffer(const char *s)
{
    char buf[72];

    strcpy(buf, s);
    printf("Buffer content: %s\n", buf);
}

int main(void)
{
    char buf[72];

    strcpy(buf, "This is a very long input string that will overflow the buffer and cause undefinfined behavior.");
    printf("Buffer content: %s\n", buf);

    return 0;
}
