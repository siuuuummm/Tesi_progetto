#include <stdio.h>
#include <stdint.h>

// Function FUN_0040048e corresponds to the core logic of the feistel-like transformation.
void process_data(uint32_t *p1, uint32_t *p2, int seed) {
    uint32_t uVar1;
    uint32_t uVar2;
    
    uVar2 = seed + 0x9e3779b9;
    // The loop runs for 0x9e3779c1 - 0x9e3779b9 = 0x18 (24) iterations.
    // However, based on the decompiler, it's checking for a specific end value.
    // Let's keep the logic as decompiled.
    do {
        uVar1 = *p1;
        *p1 = (uVar1 << 5 | uVar1 >> 0x1b) ^ *p2 ^ uVar2;
        *p2 = uVar1;
        uVar2 = uVar2 + 1;
    } while (uVar2 != seed + 0x9e3779c1U);
}

// Function FUN_004004ba is the main logic.
int main(void) {
    uint32_t local_10;
    uint32_t local_c[3];
    
    local_c[0] = 0xdeadbeef;
    local_10 = 0xcafebabe;
    printf("Originale: %08X %08X\n", 0xdeadbeef, 0xcafebabe);
    
    process_data(local_c, &local_10, 0x12345678);
    
    printf("Cifrato:   %08X %08X\n", (unsigned long)local_c[0], (unsigned long)local_10);
    return 0;
}
