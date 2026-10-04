#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint32_t uVar1;
    uint64_t uVar2;
    uint64_t uVar3;
    uint32_t uVar4;
    uint64_t uVar5;

    printf("Originale: %08X %08X\n", 0xdeadbeef, 0xcafebabe);
    uVar1 = 0x716e729f;
    uVar2 = 0xcafebabe;
    uVar3 = 0xdeadbeef;
    do {
        uVar4 = ((uint32_t)uVar3 << 0xb | (uint32_t)uVar3 >> 0x15) ^ uVar1;
        uVar1 = uVar1 + 1;
        uVar5 = (uint64_t)(uVar4 ^ (uint32_t)uVar2);
        uVar2 = uVar3;
        uVar3 = uVar5;
    } while (uVar1 != 0x716e72ab);
    printf("Cifrato:   %08X %08X\n", uVar5);
    return 0;
}
