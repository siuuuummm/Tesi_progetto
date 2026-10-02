#include <stdio.h>
#include <stdint.h>

/**
 * TEA Encryption
 * 
 * @param param_1 Pointer to the 64-bit data block (two 32-bit integers)
 * @param param_2 Pointer to the 128-bit key (four 32-bit integers)
 */
void encrypt(uint32_t *param_1, int32_t *param_2)
{
  uint32_t uVar1;
  uint32_t uVar2;
  int32_t iVar3;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  iVar3 = 0;
  do {
    iVar3 = iVar3 + -0x61c88647;
    uVar1 = uVar1 + (uVar2 * 0x10 + *param_2 ^ (uVar2 >> 5) + param_2[1] ^ iVar3 + uVar2);
    uVar2 = uVar2 + (uVar1 * 0x10 + param_2[2] ^ (uVar1 >> 5) + param_2[3] ^ iVar3 + uVar1);
  } while (iVar3 != -0x3910c8e0);
  *param_1 = uVar1;
  param_1[1] = uVar2;
}

/**
 * TEA Decryption
 * 
 * @param param_1 Pointer to the 64-bit data block (two 32-bit integers)
 * @param param_2 Pointer to the 128-bit key (four 32-bit integers)
 */
void decrypt(uint32_t *param_1, int32_t *param_2)
{
  uint32_t uVar1;
  uint32_t uVar2;
  int32_t iVar3;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  iVar3 = -0x3910c8e0;
  do {
    uVar2 = uVar2 - (uVar1 * 0x10 + param_2[2] ^ (uVar1 >> 5) + param_2[3] ^ uVar1 + iVar3);
    uVar1 = uVar1 - (uVar2 * 0x10 + *param_2 ^ (uVar2 >> 5) + param_2[1] ^ uVar2 + iVar3);
    iVar3 = iVar3 + 0x61c88647;
  } while (iVar3 != 0);
  *param_1 = uVar1;
  param_1[1] = uVar2;
}

int main(int argc, char **argv)
{
    // Example usage
    uint32_t data[2] = {0x12345678, 0x9ABCDEF0};
    int32_t key[4] = {0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10};

    printf("Original: 0x%X, 0x%X\n", data[0], data[1]);

    encrypt(data, key);
    printf("Encrypted: 0x%X, 0x%X\n", data[0], data[1]);

    decrypt(data, key);
    printf("Decrypted: 0x%X, 0x%X\n", data[0], data[1]);

    return 0;
}
