#include <stdio.h>
#include <string.h>

void FUN_004004f0(char *param_1) {
    char acStack_48[72];
    strcpy(acStack_48, param_1);
    printf("Buffer content: %s\n", acStack_48);
}

int main(void) {
    char local_48[128];
    
    // The string content is reconstructed from the decompiled labels
    // which represent the string at 0x004011e0.
    strcpy(local_48, "This is a very long input string...");

    printf("Buffer content: %s\n", local_48);
    
    return 0;
}
