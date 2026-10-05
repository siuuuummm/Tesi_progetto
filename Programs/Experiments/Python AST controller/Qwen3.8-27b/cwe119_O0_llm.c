#include <stdio.h>
#include <string.h>

/* FUN_00400476: copies param_1 into a 64-byte stack buffer and prints it. */
void print_buffer(char *param_1)
{
    char local_48[64];

    strcpy(local_48, param_1);
    printf("Buffer content: %s\n", local_48);
    return;
}

/* FUN_004004ae: main entry (RDI passed to __libc_start_main at entry). */
int main(void)
{
    print_buffer("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
