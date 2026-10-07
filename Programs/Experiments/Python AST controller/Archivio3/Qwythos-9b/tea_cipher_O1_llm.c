#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * Decompile: /tmp/re_task_qdp24hnk/out
 *
 * User functions:
 *   FUN_00400480 -> encrypt_block
 *   FUN_00400508 -> decrypt_block
 *   FUN_00400582 -> main
 */

static void encrypt_block(uint32_t *block, int32_t *key) {
  uint32_t uVar1 = block[0];
  uint32_t uVar2 = block[1];
  int32_t iVar3 = 0;

  do {
    iVar3 = iVar3 - 0x61c88647;
    uVar1 = uVar1 + (uVar2 * 0x10 + key[0] ^ (uVar2 >> 5) + key[1] ^ iVar3 + uVar2);
    uVar2 = uVar2 + (uVar1 * 0x10 + key[2] ^ (uVar1 >> 5) + key[3] ^ iVar3 + uVar1);
  } while (iVar3 != -0x3910c8e0);

  block[0] = uVar1;
  block[1] = uVar2;
}

static void decrypt_block(uint32_t *block, int32_t *key) {
  uint32_t uVar1 = block[0];
  uint32_t uVar2 = block[1];
  int32_t iVar3 = -0x3910c8e0;

  do {
    uVar2 = uVar2 - (uVar1 * 0x10 + key[2] ^ (uVar1 >> 5) + key[3] ^ uVar1 + iVar3);
    uVar1 = uVar1 - (uVar2 * 0x10 + key[0] ^ (uVar2 >> 5) + key[1] ^ uVar2 + iVar3);
    iVar3 = iVar3 + 0x61c88647;
  } while (iVar3 != 0);

  block[0] = uVar1;
  block[1] = uVar2;
}

int main(void) {
  uint32_t local_20 = 0x12345678;
  uint32_t local_1c = 0x9abcdef0;
  int32_t local_38 = 0xa56babcd;
  int32_t local_34 = 0;
  int32_t local_30 = -1;
  int32_t local_2c = 0xabcd1234;

  printf("Originale: %08X %08X\n", 0x12345678, 0x9abcdef0);
  encrypt_block(&local_20, &local_38);
  printf("Cifrato:   %08X %08X\n", (uint64_t)local_20, (uint64_t)local_1c);
  decrypt_block(&local_20, &local_38);
  printf("Decifrato: %08X %08X\n", (uint64_t)local_20, (uint64_t)local_1c);
  return 0;
}
