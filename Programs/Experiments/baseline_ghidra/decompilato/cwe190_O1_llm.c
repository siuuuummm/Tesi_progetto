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
  uint uVar1;
  int iVar2;
  int *__ptr;
  undefined8 uVar3;
  int iVar4;
  int *piVar5;
  
  if (1 < param_1) {
    setvbuf(stdout,(char *)0x0,2,0);
    uVar1 = __isoc23_strtol(*(undefined8 *)(param_2 + 8),0,10);
    if (uVar1 < 0x65) {
      __ptr = (int *)malloc((ulong)(uVar1 * 4 & 0xff));
      printf("Elementi: %u, byte allocati: %u\n",(ulong)uVar1,(ulong)(uVar1 * 4 & 0xff));
      if (uVar1 != 0) {
        iVar4 = uVar1 * 3;
        iVar2 = 1;
        uVar1 = 0;
        piVar5 = __ptr;
        do {
          *piVar5 = iVar2;
          uVar1 = uVar1 + iVar2;
          iVar2 = iVar2 + 3;
          piVar5 = piVar5 + 1;
        } while (iVar2 != iVar4 + 1);
      }
      printf("Somma: %u\n",(ulong)uVar1);
      free(__ptr);
      uVar3 = 0;
    }
    else {
      puts("Troppi elementi");
      uVar3 = 1;
    }
    return uVar3;
  }
  return 1;
}


