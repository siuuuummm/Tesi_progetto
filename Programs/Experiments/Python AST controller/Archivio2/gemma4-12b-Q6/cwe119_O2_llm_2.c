#include <stdio.h>
#include <string.h>
#include <stdint.h>

void func_00400360(void) {
    ((void (*)())0x00402ff8)();
}

void func_004003e0(void) {
    return;
}

void func_004003f0(void) {
    return;
}

void func_00400420(void) {
    return;
}

void print_buffer(char *param_1) {
    char acStack_48[72];
    strcpy(acStack_48, param_1);
    printf("Buffer content: %s\n", acStack_48);
}

int main(void) {
    print_buffer("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
