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

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 main(int param_1,long param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  ulong uVar11;
  int *__ptr;
  int *piVar12;
  int *piVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  uint uVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  
  if (param_1 < 2) {
    return 1;
  }
  setvbuf(stdout,(char *)0x0,2,0);
  uVar11 = __isoc23_strtol(*(undefined8 *)(param_2 + 8),0,10);
  uVar9 = (uint)uVar11;
  if (100 < uVar9) {
    puts("Troppi elementi");
    return 1;
  }
  __ptr = (int *)malloc((ulong)(uVar9 * 4 & 0xff));
  printf("Elementi: %u, byte allocati: %u\n",uVar11 & 0xffffffff,(ulong)(byte)(uVar9 * 4));
  iVar8 = _UNK_0040138c;
  iVar7 = _UNK_00401388;
  iVar6 = _UNK_00401384;
  iVar5 = _DAT_00401380;
  iVar4 = _UNK_0040137c;
  iVar3 = _UNK_00401378;
  iVar2 = _UNK_00401374;
  iVar1 = _DAT_00401370;
  uVar19 = uVar9;
  if (uVar9 != 0) {
    if (uVar9 - 1 < 4) {
      uVar10 = 0;
      uVar19 = 0;
    }
    else {
      iVar18 = 0;
      iVar20 = 0;
      iVar21 = 0;
      iVar22 = 0;
      piVar12 = __ptr;
      iVar23 = _DAT_00401360;
      iVar24 = _UNK_00401364;
      iVar25 = _UNK_00401368;
      iVar26 = _UNK_0040136c;
      do {
        piVar13 = piVar12 + 4;
        iVar14 = iVar23 * 3;
        iVar15 = iVar24 * 3;
        iVar16 = iVar25 * 3;
        iVar17 = iVar26 * 3;
        iVar23 = iVar23 + iVar5;
        iVar24 = iVar24 + iVar6;
        iVar25 = iVar25 + iVar7;
        iVar26 = iVar26 + iVar8;
        iVar14 = iVar14 + iVar1;
        iVar15 = iVar15 + iVar2;
        iVar16 = iVar16 + iVar3;
        iVar17 = iVar17 + iVar4;
        *piVar12 = iVar14;
        piVar12[1] = iVar15;
        piVar12[2] = iVar16;
        piVar12[3] = iVar17;
        iVar18 = iVar18 + iVar14;
        iVar20 = iVar20 + iVar15;
        iVar21 = iVar21 + iVar16;
        iVar22 = iVar22 + iVar17;
        piVar12 = piVar13;
      } while (__ptr + (uVar11 >> 2 & 0x3fffffff) * 4 != piVar13);
      uVar19 = iVar18 + iVar21 + iVar20 + iVar22;
      if ((uVar11 & 3) == 0) goto LAB_00400538;
      uVar10 = uVar9 & 0xfffffffc;
    }
    iVar1 = uVar10 * 3;
    uVar19 = iVar1 + 1 + uVar19;
    if (((uVar10 + 1 < uVar9) && (uVar19 = iVar1 + 4 + uVar19, uVar10 + 2 < uVar9)) &&
       (uVar19 = iVar1 + 7 + uVar19, uVar10 + 3 < uVar9)) {
      uVar19 = iVar1 + 10 + uVar19;
    }
  }
LAB_00400538:
  printf("Somma: %u\n",(ulong)uVar19);
  free(__ptr);
  return 0;
}


