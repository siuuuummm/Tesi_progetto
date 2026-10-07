#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

uint32_t cipher_loop(uint32_t *param_1, uint32_t *param_2, int param_3) {
    uint32_t uVar1;
    uint32_t uVar2;

    uVar2 = param_3 + 0x9e3779b9U;
    do {
        uVar1 = *param_1;
        *param_1 = (uVar1 << 5 | uVar1 >> 0x1b) ^ *param_2 ^ uVar2;
        *param_2 = uVar1;
        uVar2 = uVar2 + 1;
    } while (uVar2 != (uint32_t)(param_3 + 0x9e3779c1U));
    return 0;
}

int main(void) {
    uint32_t local_10;
    uint32_t local_c[3];

    local_c[0] = 0xdeadbeef;
    local_10 = 0xcafebabe;
    printf("Originale: %08X %08X\n", 0xdeadbeef, 0xcafebabe);
    cipher_loop(local_c, &local_10, 0x12345678);
    printf("Cifrato:   %08X %08X\n", (uint64_t)local_c[0], (uint64_t)local_10);
    return 0;
}
