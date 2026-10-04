#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t main(int param_1, long param_2)
{
  uint8_t bVar1;
  uint32_t uVar2;
  uint64_t uVar3;
  void *__ptr;
  uint32_t local_10;
  uint32_t local_c;

  if (param_1 < 2) {
    uVar3 = 1;
  }
  else {
    setvbuf(stdout, (char *)0x0, 2, 0);
    uVar2 = atoi(*(char **)(param_2 + 8));
    if (uVar2 < 0x65) {
      bVar1 = (uint8_t)(uVar2 << 2);
      __ptr = malloc((unsigned long)bVar1);
      printf("Elementi: %u, byte allocati: %u\n", uVar2, bVar1);
      local_c = 0;
      for (local_10 = 0; local_10 < uVar2; local_10 = local_10 + 1) {
        *(uint32_t *)((long)__ptr + (unsigned long)local_10 * 4) = local_10 * 3 + 1;
        local_c = local_c + *(int *)((long)__ptr + (unsigned long)local_10 * 4);
      }
      printf("Somma: %u\n", local_c);
      free(__ptr);
      uVar3 = 0;
    }
    else {
      puts("Troppi elementi");
      uVar3 = 1;
    }
  }
  return uVar3;
}