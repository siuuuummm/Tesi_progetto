#include <stdio.h>
#include <stdint.h>

uint32_t mix_function(uint32_t param_1, int32_t param_2) {
    return (param_2 + 0x9e3779b9U) ^ (param_1 << 5 | param_1 >> 0x1b);
}

void encrypt_block(uint32_t *param_1, uint32_t *param_2, int32_t param_3) {
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t local_14;
    
    for (local_14 = 0; local_14 < 8; local_14 = local_14 + 1) {
        uVar1 = *param_1;
        uVar2 = *param_2;
        uVar3 = mix_function(*param_1, (int32_t)(local_14 + param_3));
        *param_1 = uVar2 ^ uVar3;
        *param_2 = uVar1;
    }
}

int main(void) {
    uint32_t local_10;
    uint32_t local_14;
    uint32_t local_c;
    
    local_10 = 0xdeadbeef;
    local_14 = 0xcafebabe;
    local_c = 0x12345678;
    
    printf("Originale: %08X %08X\n", 0xdeadbeef, 0xcafebabe);
    encrypt_block(&local_10, &local_14, (int32_t)local_c);
    printf("Cifrato:   %08X %08X\n", (uint32_t)local_10, (uint32_t)local_14);
    
    return 0;
}
