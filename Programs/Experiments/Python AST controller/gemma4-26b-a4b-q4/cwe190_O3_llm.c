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

    int *ptr = (int *)malloc((uVar9 * 4) & 0xff);
    printf("Elementi: %u, byte allocati: %u\n", (uint32_t)uVar11, (uint32_t)((uVar9 * 4) & 0xff));

    uint32_t iVar18 = 0;
    uint32_t iVar20 = 0;
    uint32_t iVar21 = 0;
    uint32_t iVar22 = 0;
    uint32_t uVar19 = 0;
    uint32_t uVar10 = 0;

    if (uVar9 != 0) {
        if (uVar9 - 1 < 4) {
            uVar10 = 0;
            uVar19 = 0;
        } else {
            uint32_t iVar23 = 0;
            uint32_t iVar24 = 1;
            uint32_t iVar25 = 2;
            uint32_t iVar26 = 3;
            uint32_t iVar5 = 4;
            uint32_t iVar6 = 4;
            uint32_t iVar7 = 4;
            uint32_t iVar8 = 4;
            uint32_t iVar1 = 1;
            uint32_t iVar2 = 1;
            uint32_t iVar3 = 1;
            uint32_t iVar4 = 1;

            int *piVar12 = ptr;
            do {
                int *piVar13 = piVar12 + 4;
                uint32_t iVar14 = iVar23 * 3;
                uint32_t iVar15 = iVar24 * 3;
                uint32_t iVar16 = iVar25 * 3;
                uint32_t iVar17 = iVar26 * 3;

                iVar23 = iVar23 + iVar5;
                iVar24 = iVar24 + iVar6;
                iVar25 = iVar25 + iVar7;
                iVar26 = iVar26 + iVar8;

                iVar14 = iVar14 + iVar1;
                iVar15 = iVar15 + iVar2;
                iVar16 = iVar16 + iVar3;
                iVar17 = iVar17 + iVar4;

                *piVar12 = (int)iVar14;
                piVar12[1] = (int)iVar15;
                piVar12[2] = (int)iVar16;
                piVar12[3] = (int)iVar17;

                iVar18 = iVar18 + iVar14;
                iVar20 = iVar20 + iVar15;
                iVar21 = iVar21 + iVar16;
                iVar22 = iVar22 + iVar17;

                piVar12 = piVar13;
            } while (ptr + (uVar9 >> 2 & 0x3fffffff) * 4 != piVar12);

            uVar19 = iVar18 + iVar21 + iVar20 + iVar22;
            if ((uVar11 & 3) == 0) {
                goto end_of_if;
            }
            uVar10 = uVar9 & 0xfffffffc;
        }

        uint32_t iVar1_val = uVar10 * 3;
        uVar19 = iVar1_val + 1 + uVar19;
        if (((uVar10 + 1 < uVar9) && (uVar19 = iVar1_val + 4 + uVar19, uVar10 + 2 < uVar9)) &&
            (uVar19 = iVar1_val + 7 + uVar19, uVar10 + 3 < uVar9)) {
            uVar19 = iVar1_val + 10 + uVar19;
        }
    }

end_of_if:
    printf("Somma: %u\n", uVar19);
    free(ptr);
    return 0;
}
