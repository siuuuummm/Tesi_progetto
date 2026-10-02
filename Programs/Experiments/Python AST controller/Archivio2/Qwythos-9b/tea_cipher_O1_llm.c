#include <stdio.h>
#include <stdint.h>

/*
 * TEA Cipher - O1 variant
 * Decompile recovered from Ghidra
 */

/* FUN_00400480: Encrypt round */
void encrypt_round(uint32_t *state, const int32_t *key)
{
    uint32_t v0, v1;
    int32_t k0, k1, k2, k3;
    int32_t delta = -0x3910c8e0;
    
    v0 = state[0];
    v1 = state[1];
    k0 = key[0];
    k1 = key[1];
    k2 = key[2];
    k3 = key[3];
    
    do {
        v1 = v1 - (v0 * 0x10 + k2 ^ (v0 >> 5) + k3 ^ v0 + delta);
        v0 = v0 - (v1 * 0x10 + k0 ^ (v1 >> 5) + k1 ^ v1 + delta);
        delta = delta + 0x61c88647;
    } while (delta != 0);
    
    state[0] = v0;
    state[1] = v1;
}

/* FUN_00400508: Decrypt round */
void decrypt_round(uint32_t *state, const int32_t *key)
{
    uint32_t v0, v1;
    int32_t k0, k1, k2, k3;
    int32_t delta = -0x3910c8e0;
    
    v0 = state[0];
    v1 = state[1];
    k0 = key[0];
    k1 = key[1];
    k2 = key[2];
    k3 = key[3];
    
    do {
        v1 = v1 - (v0 * 0x10 + k2 ^ (v0 >> 5) + k3 ^ v0 + delta);
        v0 = v0 - (v1 * 0x10 + k0 ^ (v1 >> 5) + k1 ^ v1 + delta);
        delta = delta + 0x61c88647;
    } while (delta != 0);
    
    state[0] = v0;
    state[1] = v1;
}

/* FUN_00400582: Main function with test */
int main(void)
{
    uint32_t state[2];
    int32_t key[4];
    
    state[0] = 0x12345678;
    state[1] = 0x9abcdef0;
    
    key[0] = 0xa56babcd;
    key[1] = 0;
    key[2] = 0xffffffff;
    key[3] = 0xabcd1234;
    
    printf("Originale: %08X %08X\n", state[0], state[1]);
    
    encrypt_round(state, key);
    printf("Cifrato:   %08X %08X\n", state[0], state[1]);
    
    decrypt_round(state, key);
    printf("Decifrato: %08X %08X\n", state[0], state[1]);
    
    return 0;
}
