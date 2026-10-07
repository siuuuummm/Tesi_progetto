#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*
 * Decompilation da ghidra-mcp del binario stripped.
 * Ogni funzione e' stata esaminata con decompile_function, get_function_by_address,
 * disassemble_function. Il codice sottostante e' una traduzione fedele del decompilato.
 */

/* FUN_00400360 */
void FUN_00400360(void)
{
  (*(void(*)())0x00402ff8)();
  return;
}

/* FUN_004003b0 */
void FUN_004003b0(void)
{
  return;
}

/* FUN_004003c0 */
void FUN_004003c0(void)
{
  return;
}

/* FUN_004003f0 */
void FUN_004003f0(void)
{
  return;
}

/* FUN_00400480 */
void FUN_00400480(uint32_t *param_1, int32_t *param_2)
{
  uint32_t uVar1;
  uint32_t uVar2;
  int32_t iVar3;
  
  uVar1 = *param_1;
  uVar2 = ((uint32_t)(*(int32_t*)(param_1 + 1)));
  iVar3 = 0;
  do {
    iVar3 = iVar3 + -0x61c88647;
    uVar1 = uVar1 + (uVar2 * 0x10 + *param_2 ^ (uVar2 >> 5) + ((*(int32_t*)(param_2 + 1))) ^ iVar3 + uVar2);
    uVar2 = uVar2 + (uVar1 * 0x10 + ((*(int32_t*)(param_2 + 2))) ^ (uVar1 >> 5) + ((*(int32_t*)(param_2 + 3))) ^ iVar3 + uVar1);
  } while (iVar3 != -0x3910c8e0);
  *param_1 = uVar1;
  ((uint32_t*)(param_1 + 1))[0] = uVar2;
  return;
}

/* FUN_00400508 */
void FUN_00400508(uint32_t *param_1, int32_t *param_2)
{
  uint32_t uVar1;
  uint32_t uVar2;
  int32_t iVar3;
  
  uVar1 = *param_1;
  uVar2 = ((uint32_t)(*(int32_t*)(param_1 + 1)));
  iVar3 = -0x3910c8e0;
  do {
    uVar2 = uVar2 - (uVar1 * 0x10 + ((*(int32_t*)(param_2 + 2))) ^ (uVar1 >> 5) + ((*(int32_t*)(param_2 + 3))) ^ uVar1 + iVar3);
    uVar1 = uVar1 - (uVar2 * 0x10 + *param_2 ^ (uVar2 >> 5) + ((*(int32_t*)(param_2 + 1))) ^ uVar2 + iVar3);
    iVar3 = iVar3 + 0x61c88647;
  } while (iVar3 != 0);
  *param_1 = uVar1;
  ((uint32_t*)(param_1 + 1))[0] = uVar2;
  return;
}

/* FUN_00400582 */
uint32_t FUN_00400582(void)
{
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_20;
  uint32_t local_1c;
  
  local_38 = 0xa56babcd;
  local_34 = 0;
  local_30 = 0xffffffff;
  local_2c = 0xabcd1234;
  printf("Originale: %08X %08X\n", 0x12345678, 0x9abcdef0);
  local_20 = 0x12345678;
  local_1c = 0x9abcdef0;
  FUN_00400480(&local_20, &local_38);
  printf("Cifrato:   %08X %08X\n", (uint32_t)local_20, (uint32_t)local_1c);
  FUN_00400508(&local_20, &local_38);
  printf("Decifrato: %08X %08X\n", (uint32_t)local_20, (uint32_t)local_1c);
  return 0;
}

/* FUN_00400628 */
void FUN_00400628(void)
{
  return;
}

/* FUN_00400634 */
void FUN_00400634(void)
{
  return;
}

/* entry */
void processEntry uint32_t param_1, uint32_t param_2)
{
  uint32_t auStack_8 [8];
  
  (*(void(*)())0x00402fd8)(FUN_00400582,param_2,&auStack_8,0,0,param_1,auStack_8);
  do {
    ;
  } while( true );
}
