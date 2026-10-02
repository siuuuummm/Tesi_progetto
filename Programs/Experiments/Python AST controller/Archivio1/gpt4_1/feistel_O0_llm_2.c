#include <stdio.h>
#include <stdint.h>

// Dummy function; used as INIT/FINI hooks (not needed for business logic)
void dummy_function(void) {
    // Empty
}

// Function related to __gmon_start__, normally for profiling (no operational effect here)
void call_gmon_start(void) {
    // Empty
}

// Mixing function used in encryption (variant of TEA/XXTEA step)
uint32_t mix_uint32(uint32_t v, int round) {
    return (round + 0x9e3779b9u) ^ ((v << 5) | (v >> 27));
}

// Encrypt a two-uint32 block, 8 rounds, using 'key' as an integer (possibly as seed)
void encrypt_block(uint32_t *a, uint32_t *b, int key) {
    for (uint32_t round = 0; round < 8; ++round) {
        uint32_t old_a = *a;
        uint32_t old_b = *b;
        uint32_t temp = mix_uint32(*a, round + key);
        *a = old_b ^ temp;
        *b = old_a;
    }
}

// Main function
int main(void) {
    uint32_t a = 0xdeadbeef;
    uint32_t b = 0xcafebabe;
    int key = 0x12345678;
    printf("Originale: %08X %08X\n", a, b);
    encrypt_block(&a, &b, key);
    printf("Cifrato:   %08X %08X\n", a, b);
    return 0;
}
