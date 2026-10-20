#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
typedef unsigned char undefined; typedef unsigned char undefined1; typedef unsigned short undefined2;
typedef unsigned int undefined3; typedef unsigned int undefined4; typedef unsigned long undefined5;
typedef unsigned long undefined6; typedef unsigned long undefined7; typedef unsigned long undefined8;
typedef unsigned char byte; typedef unsigned char uchar; typedef unsigned short ushort;
typedef unsigned int uint; typedef unsigned long ulong; typedef long long longlong;
typedef unsigned long long ulonglong; typedef void code;
// main: main

undefined8 main(int param_1,long param_2)

{
  byte bVar1;
  uint uVar2;
  undefined8 uVar3;
  void *__ptr;
  uint local_10;
  uint local_c;
  
  if (param_1 < 2) {
    uVar3 = 1;
  }
  else {
    setvbuf(stdout,(char *)0x0,2,0);
    uVar2 = atoi(*(char **)(param_2 + 8));
    if (uVar2 < 0x65) {
      bVar1 = (byte)(uVar2 << 2);
      __ptr = malloc((ulong)bVar1);
      printf("Elementi: %u, byte allocati: %u\n",(ulong)uVar2,(ulong)bVar1);
      local_c = 0;
      for (local_10 = 0; local_10 < uVar2; local_10 = local_10 + 1) {
        *(uint *)((long)__ptr + (ulong)local_10 * 4) = local_10 * 3 + 1;
        local_c = local_c + *(int *)((long)__ptr + (ulong)local_10 * 4);
      }
      printf("Somma: %u\n",(ulong)local_c);
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


