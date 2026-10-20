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
void FUN_00400476(char *param_1);
// main: main

undefined8 main(void)

{
  FUN_00400476(
              "This is a very long input string that will overflow the buffer and cause undefined behavior."
              );
  return 0;
}



void FUN_00400476(char *param_1)

{
  char local_48 [64];
  
  strcpy(local_48,param_1);
  printf("Buffer content: %s\n",local_48);
  return;
}


