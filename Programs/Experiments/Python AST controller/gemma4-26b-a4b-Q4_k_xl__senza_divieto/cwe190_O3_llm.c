#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    setvbuf(stdout, NULL, 2, 0);

    long uVar11 = strtol(argv[1], NULL, 10);
    uint32_t uVar9 = (uint32_t)uVar11;

    if (uVar9 > 100) {
        puts("Troppi elementi");
        return 1;
    }

    int *__ptr = (int *)malloc((uint64_t)(uVar9 * 4 & 0xff));
    printf("Elementi: %u, byte allocati: %u\n", (uint32_t)(uVar11 & 0xffffffff), (uint32_t)((uint8_t)(uVar9 * 4)));

    int iVar1 = 1;
    int iVar2 = 1;
    int iVar3 = 1;
    int iVar4 = 1;
    int iVar5 = 4;
    int iVar6 = 4;
    int iVar7 = 4;
    int iVar8 = 4;

    int iVar23 = 0;
    int iVar24 = 1;
    int iVar25 = 2;
    int iVar26 = 3;

    uint32_t uVar19 = 0;
    uint32_t uVar10;

    if (uVar9 != 0) {
        if (uVar9 - 1 < 4) {
            uVar10 = 0;
            uVar19 = 0;
        } else {
            int iVar18 = 0;
            int iVar20 = 0;
            int iVar21 = 0;
            int iVar22 = 0;
            int *piVar12 = __ptr;

            do {
                int *piVar13 = piVar12 + 4;
                int iVar14 = iVar23 * 3;
                int iVar15 = iVar24 * 3;
                int iVar16 = iVar25 * 3;
                int iVar17 = iVar26 * 3;

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
            if ((uVar11 & 3) == 0) {
                goto PRINT_SUM;
            }
            uVar10 = uVar9 & 0xfffffffc;
        }

        int iVar1_val = (int)uVar10 * 3;
        uVar19 = (uint32_t)iVar1_val + 1 + uVar19;
        if (uVar10 + 1 < uVar9) {
            uVar19 = (uint32_t)iVar1_val + 4 + uVar19;
            if (uVar10 + 2 < uVar9) {
                uVar19 = (uint32_t)iVar1_val + 7 + uVar19;
                if (uVar10 + 3 < uVar9) {
                    uVar19 = (uint32_t)iVar1_val + 10 + uVar19;
                }
            }
        }
    }

PRINT_SUM:
    printf("Somma: %u\n", uVar19);
    free(__ptr);
    return 0;
}
