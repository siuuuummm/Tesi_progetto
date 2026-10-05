#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * Variabili globali lette dal binario:
 *   0x401360..0x40136c : stati iniziali delle 4 lane  -> {0, 1, 2, 3}
 *   0x401370..0x40137c : offset per lane (b)          -> {1, 1, 1, 1}
 *   0x401380..0x40138c : incrementi per lane (c)      -> {4, 4, 4, 4}
 */
static int st0 = 0, st1 = 1, st2 = 2, st3 = 3;   // _DAT_00401360..c
static int add0 = 1, add1 = 1, add2 = 1, add3 = 1; // _DAT_00401370..c
static int inc0 = 4, inc1 = 4, inc2 = 4, inc3 = 4; // _DAT_00401380..c

int main(int argc, char **argv)
{
    int *ptr;
    int *piVar12, *piVar13;
    int iVar14, iVar15, iVar16, iVar17;
    int iVar18, iVar20, iVar21, iVar22;
    int iVar23, iVar24, iVar25, iVar26;
    uint32_t uVar9, uVar10;
    uint64_t uVar11;
    uint32_t uVar19;

    if (argc < 2) {
        return 1;
    }
    setvbuf(stdout, (char *)0x0, 2, 0);
    uVar11 = (uint64_t)strtol(argv[1], 0, 10);
    uVar9 = (uint32_t)uVar11;
    if (100 < uVar9) {
        puts("Troppi elementi");
        return 1;
    }
    ptr = (int *)malloc((uint64_t)(uVar9 * 4 & 0xff));
    printf("Elementi: %u, byte allocati: %u\n", uVar11 & 0xffffffff, (uint64_t)(uint8_t)(uVar9 * 4));

    iVar26 = st3;  // 0x40136c
    iVar25 = st2;  // 0x401368
    iVar24 = st1;  // 0x401364
    iVar23 = st0;  // 0x401360
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
            piVar12 = ptr;
            do {
                piVar13 = piVar12 + 4;
                iVar14 = iVar23 * 3;
                iVar15 = iVar24 * 3;
                iVar16 = iVar25 * 3;
                iVar17 = iVar26 * 3;
                iVar23 = iVar23 + inc0;
                iVar24 = iVar24 + inc1;
                iVar25 = iVar25 + inc2;
                iVar26 = iVar26 + inc3;
                iVar14 = iVar14 + add0;
                iVar15 = iVar15 + add1;
                iVar16 = iVar16 + add2;
                iVar17 = iVar17 + add3;
                *piVar12 = iVar14;
                piVar12[1] = iVar15;
                piVar12[2] = iVar16;
                piVar12[3] = iVar17;
                iVar18 = iVar18 + iVar14;
                iVar20 = iVar20 + iVar15;
                iVar21 = iVar21 + iVar16;
                iVar22 = iVar22 + iVar17;
                piVar12 = piVar13;
            } while (ptr + (uVar11 >> 2 & 0x3fffffff) * 4 != piVar13);
            uVar19 = iVar18 + iVar21 + iVar20 + iVar22;
            if ((uVar11 & 3) == 0) goto fine;
            uVar10 = uVar9 & 0xfffffffc;
        }
        iVar14 = uVar10 * 3;
        uVar19 = iVar14 + 1 + uVar19;
        if (((uVar10 + 1 < uVar9) && (uVar19 = iVar14 + 4 + uVar19, uVar10 + 2 < uVar9)) &&
           (uVar19 = iVar14 + 7 + uVar19, uVar10 + 3 < uVar9)) {
            uVar19 = iVar14 + 10 + uVar19;
        }
    }
fine:
    printf("Somma: %u\n", (uint64_t)uVar19);
    free(ptr);
    return 0;
}
