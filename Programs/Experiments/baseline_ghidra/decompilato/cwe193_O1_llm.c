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
char * FUN_004004b6(char *param_1);
// main: main

undefined8 main(int param_1,long param_2)

{
  char *__s;
  char *__s_00;
  size_t sVar1;
  undefined8 *puVar2;
  
  setvbuf(stdout,(char *)0x0,2,0);
  if (1 < param_1) {
    puVar2 = (undefined8 *)(param_2 + 8);
    do {
      __s = (char *)*puVar2;
      __s_00 = (char *)FUN_004004b6(__s);
      if (__s_00 == (char *)0x0) {
        sVar1 = strlen(__s);
        printf("Nome troppo lungo: %zu caratteri\n",sVar1);
      }
      else {
        sVar1 = strlen(__s_00);
        printf("Registrato: %s (%zu caratteri)\n",__s_00,sVar1);
        free(__s_00);
      }
      puVar2 = puVar2 + 1;
    } while (puVar2 != (undefined8 *)(param_2 + 0x10 + (ulong)(param_1 - 2) * 8));
  }
  return 0;
}



char * FUN_004004b6(char *param_1)

{
  size_t sVar1;
  char *__dest;
  
  sVar1 = strlen(param_1);
  __dest = (char *)0x0;
  if (sVar1 < 0x11) {
    __dest = (char *)malloc(0x10);
    strcpy(__dest,param_1);
  }
  return __dest;
}


