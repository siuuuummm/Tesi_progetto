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
  size_t sVar1;
  int local_c;
  
  setvbuf(stdout,(char *)0x0,2,0);
  for (local_c = 1; local_c < param_1; local_c = local_c + 1) {
    __s = (char *)FUN_004004b6(*(undefined8 *)(param_2 + (long)local_c * 8));
    if (__s == (char *)0x0) {
      sVar1 = strlen(*(char **)(param_2 + (long)local_c * 8));
      printf("Nome troppo lungo: %zu caratteri\n",sVar1);
    }
    else {
      sVar1 = strlen(__s);
      printf("Registrato: %s (%zu caratteri)\n",__s,sVar1);
      free(__s);
    }
  }
  return 0;
}



char * FUN_004004b6(char *param_1)

{
  size_t sVar1;
  char *__dest;
  
  sVar1 = strlen(param_1);
  if (sVar1 < 0x11) {
    __dest = (char *)malloc(0x10);
    strcpy(__dest,param_1);
  }
  else {
    __dest = (char *)0x0;
  }
  return __dest;
}


