#include <stdio.h>
#include <stdint.h>

void encrypt_block(uint32_t *param_1, uint32_t *param_2)
{
    int i;
    int sum;
    uint32_t y;
    uint32_t x;

    x = *param_1;
    y = param_1[1];
    sum = 0;
    for (i = 0; i < 0x20; i = i + 1) {
        sum = sum + -0x61c88647;
        x = x + (param_2[1] + (y >> 5) ^ y * 0x10 + *param_2 ^ sum + y);
        y = y + (param_2[3] + (x >> 5) ^ x * 0x10 + param_2[2] ^ sum + x);
    }
    *param_1 = x;
    param_1[1] = y;
    return;
}

void decrypt_block(uint32_t *param_1, uint32_t *param_2)
{
    int i;
    int sum;
    uint32_t y;
    uint32_t x;

    x = *param_1;
    y = param_1[1];
    sum = -0x3910c8e0;
    for (i = 0; i < 0x20; i = i + 1) {
        y = y - (param_2[3] + (x >> 5) ^ x * 0x10 + param_2[2] ^ sum + x);
        x = x - (param_2[1] + (y >> 5) ^ y * 0x10 + *param_2 ^ sum + y);
        sum = sum + 0x61c88647;
    }
    *param_1 = x;
    param_1[1] = y;
    return;
}

int main(void)
{
    uint32_t key[4];
    uint32_t v[2];

    v[0] = 0x12345678;
    v[1] = 0x9abcdef0;
    key[0] = 0xa56babcd;
    key[1] = 0;
    key[2] = 0xffffffff;
    key[3] = 0xabcd1234;
    printf("Originale: %08X %08X\n", 0x12345678, 0x9abcdef0);
    encrypt_block(v, key);
    printf("Cifrato:   %08X %08X\n", (unsigned long)v[0], (unsigned long)v[1]);
    decrypt_block(v, key);
    printf("Decifrato: %08X %08X\n", (unsigned long)v[0], (unsigned long)v[1]);
    return 0;
}