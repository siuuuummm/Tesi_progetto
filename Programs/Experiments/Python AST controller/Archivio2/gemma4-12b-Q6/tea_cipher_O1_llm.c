#include <stdio.h>
#include <stdint.h>

void encrypt(uint32_t *data, int *key) {
    uint32_t uVar1;
    uint32_t uVar2;
    int iVar3;
    
    uVar1 = data[0];
    uVar2 = data[1];
    iVar3 = 0;
    do {
        iVar3 = iVar3 - 0x61c88647;
        uVar1 = uVar1 + (uVar2 * 0x10 + (key[0] ^ (uVar2 >> 5)) + (key[1] ^ iVar3) + uVar2);
        uVar2 = uVar2 + (uVar1 * 0x10 + (key[2] ^ (uVar1 >> 5)) + (key[3] ^ iVar3) + uVar1);
    } while (iVar3 != -0x3910c8e0);
    data[0] = uVar1;
    data[1] = uVar2;
}

void decrypt(uint32_t *data, int *key) {
    uint32_t uVar1;
    uint32_t uVar2;
    int iVar3;
    
    uVar1 = data[0];
    uVar2 = data[1];
    iVar3 = -0x3910c8e0;
    do {
        uVar2 = uVar2 - (uVar1 * 0x10 + (key[2] ^ (uVar1 >> 5)) + (key[3] ^ uVar1) + iVar3);
        uVar1 = uVar1 - (uVar2 * 0x10 + (key[0] ^ (uVar2 >> 5)) + (key[1] ^ uVar2) + iVar3);
        iVar3 = iVar3 + 0x61c88647;
    } while (iVar3 != 0);
    data[0] = uVar1;
    data[1] = uVar2;
}

int main(void) {
    uint32_t local_20 = 0x12345678;
    uint32_t local_1c = 0x9abcdef0;
    uint32_t local_38 = 0xa56babcd;
    int local_34 = 0;
    int local_30 = 0xffffffff;
    int local_2c = 0xabcd1234;
    
    // The key seems to be constructed from local_34, local_30, local_2c, and some other values.
    // In the original decompile, FUN_00400582 passes &local_20 and &local_38.
    // local_38 is used as the key array.
    
    // Since the exact order of key elements in the array passed to encrypt/decrypt
    // is local_38[0..3], we map them as follows:
    int key[4];
    key[0] = local_34;
    key[1] = local_30;
    key[2] = local_2c;
    key[3] = 0; // local_38 was 0xa56babcd, but passed as a pointer to an array of 4 ints.
    // Wait, let's look at the decompile of FUN_00400582 again.
    // local_38 = 0xa56babcd; (This is one 32-bit int)
    // local_34 = 0;
    // local_30 = 0xffffffff;
    // local_2c = 0xabcd1234;
    // These are 4 consecutive 32-bit integers on the stack.
    // When passing &local_38, it points to local_38, then local_34, local_30, local_2c.
    
    key[0] = local_38;
    key[1] = local_34;
    key[2] = local_30;
    key[3] = local_2c;

    printf("Originale: %08X %08X\n", local_20, local_1c);
    
    uint32_t data[2] = {local_20, local_1c};
    
    encrypt(data, key);
    printf("Cifrato:   %08X %08X\n", data[0], data[1]);
    
    decrypt(data, key);
    printf("Decifrato: %08X %08X\n", data[0], data[1]);
    
    return 0;
}
