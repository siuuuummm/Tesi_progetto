void FUN_004003b0(void) { return; }
void FUN_004003c0(void) { return; }
void FUN_004003f0(void) { return; }
void FUN_00400360(void) { ((void (*)())(*(void **)0x00402ff8))(); return; }
unsigned char DAT_00403010[] = { /* TODO: fill values by further string/memory dump */ };
#include <stdio.h>

int main(void) {
    int iVar1;
    unsigned char bVar2;
    unsigned char bVar3;
    unsigned int local_10;
    unsigned char local_9;

    local_9 = 0x42;
    local_10 = 0;
    while (local_10 < 8) {
        iVar1 = local_10 + 1;
        bVar2 = DAT_00403010[(int)local_10];
        local_10 = local_10 + 2;
        bVar3 = DAT_00403010[iVar1];
        if (bVar2 == 3) {
            local_9 = (unsigned char)(((unsigned int)local_9 >> (8 - bVar3 & 0x1f)) | (local_9 << (bVar3 & 0x1f)));
        } else {
            if (3 < bVar2) break;
            if (bVar2 == 1) {
                local_9 = local_9 ^ bVar3;
            } else {
                if (bVar2 != 2) break;
                local_9 = (unsigned char)(local_9 + bVar3);
            }
        }
    }
    printf("Risultato finale: 0x%02X\n", (unsigned long)local_9);
    return 0;
}

