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

bool main(int param_1,long param_2)

{
  if (param_1 < 2) {
    printf("Uso: %s <messaggio>\n","logger");
  }
  else {
    printf("[log] ");
    printf(*(char **)(param_2 + 8));
    putchar(10);
  }
  return param_1 < 2;
}


