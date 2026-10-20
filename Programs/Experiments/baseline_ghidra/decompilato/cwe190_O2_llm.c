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
  int iVar1;
  uint uVar2;
  int iVar3;
  int *__ptr;
  undefined8 uVar4;
  int *piVar5;
  
  if (1 < param_1) {
    setvbuf(stdout,(char *)0x0,2,0);
    uVar2 = __isoc23_strtol(*(undefined8 *)(param_2 + 8),0,10);
    if (uVar2 < 0x65) {
      __ptr = (int *)malloc((ulong)(uVar2 * 4 & 0xff));
      printf("Elementi: %u, byte allocati: %u\n",(ulong)uVar2,(ulong)(byte)(uVar2 * 4));
      if (uVar2 != 0) {
        iVar1 = uVar2 * 3;
        iVar3 = 1;
        uVar2 = 0;
        piVar5 = __ptr;
        do {
          *piVar5 = iVar3;
          uVar2 = uVar2 + iVar3;
          iVar3 = iVar3 + 3;
          piVar5 = piVar5 + 1;
        } while (iVar3 != iVar1 + 1);
      }
      printf("Somma: %u\n",(ulong)uVar2);
      free(__ptr);
      uVar4 = 0;
    }
    else {
      puts("Troppi elementi");
      uVar4 = 1;
    }
    return uVar4;
  }
  return 1;
}


