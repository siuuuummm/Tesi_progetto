#include <stdio.h>
#include <string.h>
#include <stdint.h>

void call_hidden_ptr(void) {
    (*(code *)0x00402ff8)();
}

void unused_function_1(void) {
    return;
}

void unused_function_2(void) {
    return;
}

void unused_function_3(void) {
    return;
}

void print_buffer(char *param_1) {
    char local_48[64];
    strcpy(local_48, param_1);
    printf("Buffer content: %s\n", local_48);
}

uint64_t main(void) {
    print_buffer("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
