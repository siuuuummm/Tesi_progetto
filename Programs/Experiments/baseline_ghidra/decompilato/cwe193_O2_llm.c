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
  undefined8 *puVar1;
  char *__s;
  uint uVar2;
  size_t sVar3;
  char *__ptr;
  uint uVar4;
  ulong uVar5;
  undefined8 *puVar6;
  
  setvbuf(stdout,(char *)0x0,2,0);
  if (1 < param_1) {
    puVar6 = (undefined8 *)(param_2 + 8);
    puVar1 = (undefined8 *)(param_2 + 0x10 + (ulong)(param_1 - 2) * 8);
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
              *(undefined2 *)(__ptr + ((uVar5 & 0xffffffff) - 2)) =
                   *(undefined2 *)(__s + ((uVar5 & 0xffffffff) - 2));
            }
          }
          else {
            *(undefined4 *)__ptr = *(undefined4 *)__s;
            *(undefined4 *)(__ptr + ((uVar5 & 0xffffffff) - 4)) =
                 *(undefined4 *)(__s + ((uVar5 & 0xffffffff) - 4));
          }
        }
        else {
          *(undefined8 *)(__ptr + ((uVar5 & 0xffffffff) - 8)) =
               *(undefined8 *)(__s + ((uVar5 & 0xffffffff) - 8));
          if (7 < uVar2 - 1) {
            uVar5 = 0;
            do {
              uVar4 = (int)uVar5 + 8;
              *(undefined8 *)(__ptr + uVar5) = *(undefined8 *)(__s + uVar5);
              uVar5 = (ulong)uVar4;
            } while (uVar4 < (uVar2 - 1 & 0xfffffff8));
          }
        }
        printf("Registrato: %s (%zu caratteri)\n",__ptr,sVar3);
        puVar6 = puVar6 + 1;
        free(__ptr);
        if (puVar6 == puVar1) {
          return 0;
        }
      }
      puVar6 = puVar6 + 1;
      printf("Nome troppo lungo: %zu caratteri\n",sVar3);
    } while (puVar6 != puVar1);
  }
  return 0;
}


