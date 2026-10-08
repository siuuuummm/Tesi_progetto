#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int param_1, char **param_2)
{
  uint8_t bVar1;
  uint32_t uVar2;
  void *__ptr;
  uint32_t i;
  uint32_t sum;

  if (param_1 < 2) {
    return 1;
  }
  else {
    setvbuf(stdout, (char *)0x0, 2, 0);
    uVar2 = atoi(param_2[1]);
    if (uVar2 < 0x65) {
      bVar1 = (uint8_t)(uVar2 << 2);
      __ptr = malloc((unsigned long)bVar1);
      printf("Elementi: %u, byte allocati: %u\n", (unsigned long)uVar2, (unsigned long)bVar1);
      sum = 0;
      for (i = 0; i < uVar2; i = i + 1) {
        *(uint32_t *)((long)__ptr + (unsigned long)i * 4) = i * 3 + 1;
        sum = sum + *(int *)((long)__ptr + (unsigned long)i * 4);
      }
      printf("Somma: %u\n", (unsigned long)sum);
      free(__ptr);
      return 0;
    }
    else {
      puts("Troppi elementi");
      return 1;
    }
  }
}