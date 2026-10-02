#include <stdio.h>
#include <stdint.h>

// TEA (Tiny Encryption Algorithm)
// Implements encryption
void tea_encrypt(uint32_t *v, uint32_t *k) {
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = 0;
    uint32_t delta = 0x9e3779b9; // 0x61c88647 * -1

    // Based on decompiled FUN_00400480
    // The decompilation shows: iVar3 = iVar3 + -0x61c88647
    // This is equivalent to sum -= 0x61c88647
    // Which matches the standard TEA delta adjustment
    
    // Decompiled loop:
    // iVar3 = 0;
    // do {
    //   iVar3 = iVar3 + -0x61c88647;
    //   uVar1 = uVar1 + (uVar2 * 0x10 + *param_2 ^ (uVar2 >> 5) + param_2[1] ^ iVar3 + uVar2);
    //   uVar2 = uVar2 + (uVar1 * 0x10 + param_2[2] ^ (uVar1 >> 5) + param_2[3] ^ iVar3 + uVar1);
    // } while (iVar3 != -0x3910c8e0);
    
    // Let's implement it carefully to match the decompilation exactly.
    int32_t iVar3 = 0;
    uint32_t uVar1 = v0;
    uint32_t uVar2 = v1;

    do {
        iVar3 = iVar3 - 0x61c88647;
        uVar1 = uVar1 + ((uVar2 << 4) + k[0] ^ (uVar2 >> 5) + k[1] ^ iVar3 + uVar2);
        uVar2 = uVar2 + ((uVar1 << 4) + k[2] ^ (uVar1 >> 5) + k[3] ^ iVar3 + uVar1);
    } while (iVar3 != -0x3910c8e0);
    
    v[0] = uVar1;
    v[1] = uVar2;
}

// Implements decryption
void tea_decrypt(uint32_t *v, uint32_t *k) {
    uint32_t uVar1 = v[0];
    uint32_t uVar2 = v[1];
    int32_t iVar3 = -0x3910c8e0;

    // Decompiled loop:
    // iVar3 = -0x3910c8e0;
    // do {
    //   uVar2 = uVar2 - (uVar1 * 0x10 + param_2[2] ^ (uVar1 >> 5) + param_2[3] ^ uVar1 + iVar3);
    //   uVar1 = uVar1 - (uVar2 * 0x10 + *param_2 ^ (uVar2 >> 5) + param_2[1] ^ uVar2 + iVar3);
    //   iVar3 = iVar3 + 0x61c88647;
    // } while (iVar3 != 0);

    do {
        uVar2 = uVar2 - ((uVar1 << 4) + k[2] ^ (uVar1 >> 5) + k[3] ^ uVar1 + iVar3);
        uVar1 = uVar1 - ((uVar2 << 4) + k[0] ^ (uVar2 >> 5) + k[1] ^ uVar2 + iVar3);
        iVar3 = iVar3 + 0x61c88647;
    } while (iVar3 != 0);
    
    v[0] = uVar1;
    v[1] = uVar2;
}

int main(void) {
    uint32_t key[4] = {0xa56babcd, 0, 0xffffffff, 0xabcd1234};
    uint32_t data[2] = {0x12345678, 0x9abcdef0};

    printf("Originale: %08X %08X\n", data[0], data[1]);
    
    tea_encrypt(data, key);
    printf("Cifrato:   %08X %08X\n", data[0], data[1]);
    
    tea_decrypt(data, key);
    printf("Decifrato: %08X %08X\n", data[0], data[1]);
    
    return 0;
}
