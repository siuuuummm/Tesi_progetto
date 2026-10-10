#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

int main(int param_1, long param_2)
{
  uint64_t *puVar1;
  char *__s;
  uint uVar2;
  size_t sVar3;
  char *__ptr;
  uint uVar4;
  unsigned long uVar5;
  uint64_t *puVar6;

  setvbuf(stdout, (char *)0x0, 2, 0);
  if (1 < param_1) {
    puVar6 = (uint64_t *)(param_2 + 8);
    puVar1 = (uint64_t *)(param_2 + 0x10 + (unsigned long)(param_1 - 2) * 8);
    do {
      while( true ) {
        __s = (char *)*puVar6;
        sVar3 = strlen(__s);
        if (0x10 < sVar3) break;
        __ptr = (char *)malloc(0x10);
        uVar5 = sVar3 + 1;
        uVar2 = (uint)uVar5;
        if (uVar2 < 8) {
          if ((uVar5 & 4) == 0) {
            if ((uVar2 != 0) && (*__ptr = *__s, (uVar5 & 2) != 0)) {
              *(uint16_t *)(__ptr + ((uVar5 & 0xffffffff) - 2)) =
                  *(uint16_t *)(__s + ((uVar5 & 0xffffffff) - 2));
            }
          }
          else {
            *(uint32_t *)__ptr = *(uint32_t *)__s;
            *(uint32_t *)(__ptr + ((uVar5 & 0xffffffff) - 4)) =
                *(uint32_t *)(__s + ((uVar5 & 0xffffffff) - 4));
          }
        }
        else {
          *(uint64_t *)(__ptr + ((uVar5 & 0xffffffff) - 8)) =
              *(uint64_t *)(__s + ((uVar5 & 0xffffffff) - 8));
          if (7 < uVar2 - 1) {
            uVar5 = 0;
            do {
              uVar4 = (int)uVar5 + 8;
              *(uint64_t *)(__ptr + uVar5) = *(uint64_t *)(__s + uVar5);
              uVar5 = (ulong)uVar4;
            } while (uVar4 < (uVar2 - 1 & 0xfffffff8));
          }
        }
        printf("Registrato: %s (%zu caratteri)\n", __ptr, sVar3);
        puVar6 = puVar6 + 1;
        free(__ptr);
        if (puVar6 == puVar1) {
          return 0;
        }
      }
      puVar6 = puVar6 + 1;
      printf("Nome troppo lungo: %zu caratteri\n", sVar3);
    } while (puVar6 != puVar1);
  }
  return 0;
}
