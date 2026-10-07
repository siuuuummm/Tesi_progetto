#include <stdio.h>
#include <stdint.h>

uint32_t rotate_xor_encrypt(uint32_t param_1, int32_t param_2) {
    return (param_1 << 0xb | param_1 >> 0x15) ^ (uint32_t)(param_2 + 0x5f3a1c27U);
}

void block_cipher_encrypt(uint32_t *param_1, uint32_t *param_2, int32_t param_3) {
    uint32_t uVar1;
    uint32_t uVar2;

    uVar1 = *param_1;
    *param_1 = (uint32_t)(param_3 + 0x5f3a1c27U) ^ *param_2 ^ (uVar1 << 0xb | uVar1 >> 0x15);
    *param_2 = uVar1;

    uVar2 = *param_1;
    *param_1 = (uint32_t)(param_3 + 0x5f3a1c28U) ^ uVar1 ^ (uVar2 << 0xb | uVar2 >> 0x15);
    *param_2 = uVar2;

    uVar1 = *param_1;
    *param_1 = (uint32_t)(param_3 + 0x5f3a1c29U) ^ uVar2 ^ (uVar1 << 0xb | uVar1 >> 0x15);
    *param_2 = uVar1;

    uVar2 = *param_1;
    *param_1 = (uint32_t)(param_3 + 0x5f3a1c2aU) ^ uVar1 ^ (uVar2 << 0xb | uVar2 >> 0x15);
    *param_2 = uVar2;

    uVar1 = *param_1;
    *param_1 = (uint32_t)(param_3 + 0x5f3a1c2bU) ^ uVar2 ^ (uVar1 << 0xb | uVar1 >> 0x15);
    *param_2 = uVar1;

    uVar2 = *param_1;
    *param_1 = (uint32_t)(param_3 + 0x5f3a1c2cU) ^ uVar1 ^ (uVar2 << 0xb | uVar2 >> 0x15);
    *param_2 = uVar2;

    uVar1 = *param_1;
    *param_1 = (uint32_t)(param_3 + 0x5f3a1c2dU) ^ uVar2 ^ (uVar1 << 0xb | uVar1 >> 0x15);
    *param_2 = uVar1;

    uVar2 = *param_1;
    *param_1 = (uint32_t)(param_3 + 0x5f3a1c2eU) ^ uVar1 ^ (uVar2 << 0xb | uVar2 >> 0x15);
    *param_2 = uVar2;

    uVar1 = *param_1;
    *param_1 = (uint32_t)(param_3 + 0x5f3a1c2fU) ^ uVar2 ^ (uVar1 << 0xb | uVar1 >> 0x15);
    *param_2 = uVar1;

    uVar2 = *param_1;
    *param_1 = (uint32_t)(param_3 + 0x5f3a1c30U) ^ uVar1 ^ (uVar2 << 0xb | uVar2 >> 0x15);
    *param_2 = uVar2;

    uVar1 = *param_1;
    *param_1 = (uint32_t)(param_3 + 0x5f3a1c31U) ^ uVar2 ^ (uVar1 << 0xb | uVar1 >> 0x15);
    *param_2 = uVar1;

    uVar2 = *param_1;
    *param_1 = (uint32_t)(param_3 + 0x5f3a1c32U) ^ uVar1 ^ (uVar2 << 0xb | uVar2 >> 0x15);
    *param_2 = uVar2;
}

int main() {
    printf("Originale: %08X %08X\n", 0xdeadbeef, 0xcafebabe);
    printf("Cifrato:   %08X %08X\n", 0xd8e82285, 0x2ff2d908);
    return 0;
}
