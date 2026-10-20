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
  int iVar2;
  undefined8 uVar3;
  char *__dest;
  char *__dest_00;
  
  if (param_1 < 3) {
    uVar3 = 1;
  }
  else {
    setvbuf(stdout,(char *)0x0,2,0);
    __dest = (char *)malloc(0x20);
    memset(__dest,0,0x20);
    strncpy(__dest,*(char **)(param_2 + 8),0x17);
    __dest[0x1c] = -0x18;
    __dest[0x1d] = '\x03';
    __dest[0x1e] = '\0';
    __dest[0x1f] = '\0';
    printf("Sessione %d aperta per %s\n",(ulong)*(uint *)(__dest + 0x1c),__dest);
    iVar1 = strcmp(*(char **)(param_2 + 0x10),"logout");
    if (iVar1 == 0) {
      free(__dest);
      puts("Logout eseguito");
    }
    __dest_00 = (char *)malloc(0x20);
    memset(__dest_00,0,0x20);
    strncpy(__dest_00,"promemoria",0x17);
    if (param_1 < 4) {
      iVar2 = 0;
    }
    else {
      iVar2 = atoi(*(char **)(param_2 + 0x18));
    }
    *(int *)(__dest_00 + 0x18) = iVar2;
    __dest_00[0x1c] = '\a';
    __dest_00[0x1d] = '\0';
    __dest_00[0x1e] = '\0';
    __dest_00[0x1f] = '\0';
    if (*(int *)(__dest + 0x18) == 0) {
      printf("Accesso utente per %s\n",__dest);
    }
    else {
      printf("Accesso amministratore per %s\n",__dest);
    }
    free(__dest_00);
    if (iVar1 != 0) {
      free(__dest);
    }
    uVar3 = 0;
  }
  return uVar3;
}


