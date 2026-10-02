#include <stdio.h>
#include <stdint.h>

/**
 * Function corresponding to FUN_00400466
 * Performs a mixing operation involving a shift and an XOR with a constant.
 */
uint32_t mix_function(uint32_t value, int index) {
    return (uint32_t)(index + 0x9e3779b9U) ^ (value << 5 | value >> 27);
}

/**
 * Function corresponding to FUN_00400484
 * Implements a Feistel-like network structure.
 */
void feistel_network(uint32_t *left, uint32_t *right, int key_offset) {
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t i;

    for (i = 0; i < 8; i = i + 1) {
        uVar1 = *left;
        uVar2 = *right;
        uVar3 = mix_function(*left, i + key_offset);
        *left = uVar2 ^ uVar3;
        *right = uVar1;
    }
}

/**
 * Function corresponding to FUN_004004ec
 * The main logic of the program.
 */
int main(void) {
    uint32_t local_14;
    uint32_t local_10;
    uint32_t local_c;

    local_10 = 0xdeadbeef;
    local_14 = 0xcafebabe;
    local_c = 0x12345678;

    printf("Originale: %08X %08X\n", 0xdeadbeef, 0xcafebabe);
    feistel_network(&local_10, &local_14, local_c);
    printf("Cifrato:   %08X %08X\n", (uint32_t)local_10, (uint32_t)local_14);

    return 0;
}
