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

int main(int param_1,long param_2)

{
  int iVar1;
  char *__dest;
  long lVar2;
  char *pcVar3;
  byte bVar4;
  
  bVar4 = 0;
  iVar1 = 1;
  if (2 < param_1) {
    setvbuf(stdout,(char *)0x0,2,0);
    __dest = (char *)malloc(0x20);
    pcVar3 = __dest;
    for (lVar2 = 8; lVar2 != 0; lVar2 = lVar2 + -1) {
      pcVar3[0] = '\0';
      pcVar3[1] = '\0';
      pcVar3[2] = '\0';
      pcVar3[3] = '\0';
      pcVar3 = pcVar3 + (ulong)bVar4 * -8 + 4;
    }
    strncpy(__dest,*(char **)(param_2 + 8),0x17);
    __dest[0x1c] = -0x18;
    __dest[0x1d] = '\x03';
    __dest[0x1e] = '\0';
    __dest[0x1f] = '\0';
    printf("Sessione %d aperta per %s\n",1000,__dest);
    iVar1 = strcmp(*(char **)(param_2 + 0x10),"logout");
    if (iVar1 == 0) {
      free(__dest);
      puts("Logout eseguito");
    }
    if (3 < param_1) {
      __isoc23_strtol(*(undefined8 *)(param_2 + 0x18),0,10);
    }
    if (*(int *)(__dest + 0x18) == 0) {
      printf("Accesso utente per %s\n",__dest);
    }
    else {
      printf("Accesso amministratore per %s\n",__dest);
    }
    if (iVar1 != 0) {
      free(__dest);
      iVar1 = 0;
    }
  }
  return iVar1;
}


