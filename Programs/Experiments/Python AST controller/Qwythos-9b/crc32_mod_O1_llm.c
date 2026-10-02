#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static uint32_t table[256];

static void FUN_004004a0(void)
{
  uint64_t uVar5;
  uint64_t uVar3;
  uint64_t uVar1;
  uint64_t uVar2;

  uVar5 = 0;
  do
  {
    uVar3 = uVar5 & 0xffffffff;
    uVar1 = uVar3 >> 1;
    uVar2 = uVar3 & 1;
    uVar3 = (uint32_t)((uint64_t)(uVar3 >> 1) ^ 0xa5c3e10f);
    if (uVar2 == 0)
    {
      uVar3 = uVar1;
    }
    table[uVar5] = (uint32_t)uVar3;
    uVar5 = uVar5 + 1;
  } while (uVar5 != 0x100);
}

static uint32_t FUN_004004ef(void *param_1, int param_2)
{
  uint32_t uVar1;
  void *pbVar2;

  if (param_2 < 1)
  {
    uVar1 = 0x13579bdf;
  }
  else
  {
    pbVar2 = param_1 + param_2;
    uVar1 = 0x13579bdf;
    do
    {
      uVar1 = uVar1 >> 8 ^ ((uint32_t)(table[((uint8_t)(uVar1 ^ *(uint8_t *)param_1))]));
      param_1 = (void *)((uint8_t *)param_1 + 1);
    } while (param_1 != pbVar2);
  }
  return uVar1 ^ 0x2468ace0;
}

int main(void)
{
  FUN_004004a0();
  char *local_38[4];
  char *__s;
  size_t sVar2;
  uint32_t uVar1;

  local_38[0] = "";
  local_38[1] = "a";
  local_38[2] = "abc";
  local_38[3] = "Hello, World!";

  for (__s = local_38; __s != local_38 + 4; __s = (__s) + 1)
  {
    sVar2 = strlen(__s);
    uVar1 = FUN_004004ef(__s, sVar2 & 0xffffffff);
    printf("CRC32(\"%s\") = 0x%08X\n", __s, uVar1);
  }
  return 0;
}
