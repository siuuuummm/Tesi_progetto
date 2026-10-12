#include <stdio.h>
#include <string.h>

/* FUN_00400476: copies param_1 into a 64-byte stack buffer with strcpy,
   then prints it with printf("Buffer content: %s\n", buffer). */
void FUN_00400476(char *param_1)
{
    char buffer[64];

    strcpy(buffer, param_1);
    printf("Buffer content: %s\n", buffer);
    return;
}

/* FUN_0040049e: main (passed to __libc_start_main in entry). */
undefined8 FUN_0040049e(void)
{
    FUN_00400476(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}

int main(void)
{
    return (int)FUN_0040049e();
}