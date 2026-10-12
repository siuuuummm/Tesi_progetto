#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void unsafe_copy_and_print(char *src)
{
    char buffer[72];
    strcpy(buffer, src);
    printf("Buffer content: %s\n", buffer);
}

int main(void)
{
    char buf[72];
    strcpy(buf, "This is a very long input string that will overflow the buffer and cause undefined behavior.");
    printf("Buffer content: %s\n", buf);
    return 0;
}