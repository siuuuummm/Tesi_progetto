#include <stdio.h>

/**
 * Reconstructed from FUN_00400380
 * This function prints the original and encrypted values.
 */
void print_feistel_results(void) {
    printf("Originale: %08X %08X\n", 0xdeadbeef, 0xcafebabe);
    printf("Cifrato:   %08X %08X\n", 0x9dee733b, 0xc7802f9d);
}

/**
 * Reconstructed from FUN_004003d8
 * This function acts as the entry point for the main logic, 
 * calling the result printer and then entering an infinite loop.
 */
int main(void) {
    print_feistel_results();
    
    // Reconstructed from the infinite loop in FUN_004003d8
    while (1) {
        // Do nothing block with infinite loop
    }
    
    return 0;
}
