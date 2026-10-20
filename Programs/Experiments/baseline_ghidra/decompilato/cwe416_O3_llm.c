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

undefined1  [16] main(int param_1,long param_2,undefined8 param_3,ulong param_4)

{
  undefined1 auVar1 [16];
  int iVar2;
  char *__dest;
  undefined1 auVar3 [16];
  
  if (param_1 < 3) {
    auVar3._8_8_ = param_3;
    auVar3._0_8_ = 1;
    return auVar3;
  }
  setvbuf(stdout,(char *)0x0,2,0);
  __dest = (char *)calloc(0x20,1);
  strncpy(__dest,*(char **)(param_2 + 8),0x17);
  __dest[0x1c] = -0x18;
  __dest[0x1d] = '\x03';
  __dest[0x1e] = '\0';
  __dest[0x1f] = '\0';
  printf("Sessione %d aperta per %s\n",1000,__dest);
  iVar2 = strcmp(*(char **)(param_2 + 0x10),"logout");
  if (iVar2 == 0) {
    free(__dest);
    puts("Logout eseguito");
  }
  if (param_1 != 3) {
    __isoc23_strtol(*(undefined8 *)(param_2 + 0x18),0,10);
  }
  if (*(int *)(__dest + 0x18) == 0) {
    printf("Accesso utente per %s\n",__dest);
  }
  else {
    printf("Accesso amministratore per %s\n",__dest);
  }
  if (iVar2 != 0) {
    free(__dest);
  }
  auVar1._8_8_ = 0;
  auVar1._0_8_ = param_4;
  return auVar1 << 0x40;
}


