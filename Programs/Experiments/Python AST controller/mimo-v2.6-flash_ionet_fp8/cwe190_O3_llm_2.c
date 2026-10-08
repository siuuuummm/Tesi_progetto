#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
 * Dati in .rodata letti esattamente dai riferimenti del main:
 *   0x00401360: dword {0, 1, 2, 3}   (vettore iniziale degli indici per lane)
 *   0x00401370: dword {1, 1, 1, 1}   (addendo costante per lane)
 *   0x00401380: dword {4, 4, 4, 4}   (incremento per lane)
 */
static const int DAT_00401360[4] = {0, 1, 2, 3};
static const int DAT_00401370[4] = {1, 1, 1, 1};
static const int DAT_00401380[4] = {4, 4, 4, 4};

/* FUN_00400400: entry point passato a __libc_start_main */
int main(int param_1, long param_2)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint32_t uVar9;
  uint32_t uVar10;
  uint64_t uVar11;
  int *__ptr;
  int *piVar12;
  int *piVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  uint32_t uVar19;
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
  setvbuf(stdout, (char *)0x0, 2, 0);
  uVar11 = (uint64_t)__isoc23_strtol(*(char **)(param_2 + 8), (char *)0, 10);
  uVar9 = (uint32_t)uVar11;
  if (100 < uVar9) {
    puts("Troppi elementi");
    return 1;
  }
  __ptr = (int *)malloc((uint64_t)(uVar9 * 4 & 0xff));
  printf("Elementi: %u, byte allocati: %u\n",
         (unsigned int)(uVar11 & 0xffffffff),
         (unsigned int)(uint8_t)(uVar9 * 4));
  iVar8 = DAT_00401380[3];
  iVar7 = DAT_00401380[2];
  iVar6 = DAT_00401380[1];
  iVar5 = DAT_00401380[0];
  iVar4 = DAT_00401370[3];
  iVar3 = DAT_00401370[2];
  iVar2 = DAT_00401370[1];
  iVar1 = DAT_00401370[0];
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
      iVar23 = DAT_00401360[0];
      iVar24 = DAT_00401360[1];
      iVar25 = DAT_00401360[2];
      iVar26 = DAT_00401360[3];
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
  printf("Somma: %u\n", (unsigned int)uVar19);
  free(__ptr);
  return 0;
}