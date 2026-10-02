#include <stdio.h>
#include <stdlib.h>

void call_external_function_wrapper(void);
void empty_function_1(void);
void empty_function_2(void);
void empty_function_3(void);
void encode_decode_chain(unsigned char *param_1, int param_2);

// Entry point wrapper: invokes main via __libc_start_main. Not part of user C code.
// Ghidra artifact, not included in main source. 

int main(void) {
    unsigned char *ptr1;
    unsigned char *ptr2;

    ptr1 = (unsigned char *)malloc(0x10);
    ptr2 = (unsigned char *)malloc(0x10);
    // Clear the next pointer
    *((unsigned long *)(ptr2 + 8)) = 0;
    *ptr2 = 0xe0;
    puts("Integrity check failed.");
    // Free a chain (dummy loop to free what was malloc'd)
    while (1) {
        unsigned char *tmp = ptr2;
        free(ptr1);
        if (tmp == NULL) break;
        ptr2 = (unsigned char *)(*((unsigned long *)(tmp + 8)));
        ptr1 = tmp;
    }
    return 0;
}

void call_external_function_wrapper(void) {
    ((void (*)())(*(void **)0x00402ff8))();
}

void empty_function_1(void) {
    // Does nothing
}

void empty_function_2(void) {
    // Does nothing
}

void empty_function_3(void) {
    // Does nothing
}

void encode_decode_chain(unsigned char *param_1, int param_2) {
    if (param_1 != NULL) {
        if (param_2 == 0) {
            // Decode: for each element in the chain
            do {
                *param_1 = (*param_1 - 1) ^ 0x55;
                param_1 = (unsigned char *)(*((unsigned long *)(param_1 + 8)));
            } while (param_1 != NULL);
            return;
        }
        // Encode: for each element in the chain
        do {
            *param_1 = (*param_1 ^ 0x55) + 1;
            param_1 = (unsigned char *)(*((unsigned long *)(param_1 + 8)));
        } while (param_1 != NULL);
    }
}
