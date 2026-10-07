#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

extern void _0x402ff8(void);

void dummy_call(void) {
    _0x402ff8();
}

void unused_01(void) {
    return;
}

void unused_02(void) {
    return;
}

void unused_03(void) {
    return;
}

void encrypt(uint32_t *param_1, int32_t *param_2) {
    int32_t local_18;
    int32_t local_14;
    uint32_t local_10;
    uint32_t local_c;

    local_c = *param_1;
    local_10 = param_1[1];
    local_14 = 0;
    for (local_18 = 0; local_18 < 0x20; local_18 = local_18 + 1) {
        local_14 = local_14 + -0x61c88647;
        local_c = local_c + (param_2[1] + (local_10 >> 5) ^
                            local_10 * 0x10 + *param_2 ^ local_14 + local_10);
        local_10 = local_10 +
                   (param_2[3] + (local_c >> 5) ^ local_c * 0x10 + param_2[2] ^ local_14 + local_c);
    }
    *param_1 = local_c;
    param_1[1] = local_10;
}

void decrypt(uint32_t *param_1, int32_t *param_2) {
    int32_t local_18;
    int32_t local_14;
    uint32_t local_10;
    uint32_t local_c;

    local_c = *param_1;
    local_10 = param_1[1];
    local_14 = -0x3910c8e0;
    for (local_18 = 0; local_18 < 0x20; local_18 = local_18 + 1) {
        local_10 = local_10 -
                   (param_2[3] + (local_c >> 5) ^ local_c * 0x10 + param_2[2] ^ local_14 + local_c);
        local_c = local_c - (param_2[1] + (local_10 >> 5) ^
                            local_10 * 0x10 + *param_2 ^ local_14 + local_10);
        local_14 = local_14 + 0x61c88647;
    }
    *param_1 = local_c;
    param_1[1] = local_10;
}

int main(void) {
    uint32_t local_10;
    uint32_t local_c;
    uint32_t local_28;
    uint32_t local_24;
    uint32_t local_20;
    uint32_t local_1c;

    local_10 = 0x12345678;
    local_c = 0x9abcdef0;
    local_28 = 0xa56babcd;
    local_24 = 0;
    local_20 = 0xffffffff;
    local_1c = 0xabcd1234;

    printf("Originale: %08X %08X\n", 0x12345678, 0x9abcdef0);
    encrypt(&local_10, &local_28);
    printf("Cifrato:   %08X %08X\n", (uint32_t)local_10, (uint32_t)local_c);
    decrypt(&local_10, &local_28);
    printf("Decifrato: %08X %08X\n", (uint32_t)local_10, (uint32_t)local_c);

    return 0;
}
