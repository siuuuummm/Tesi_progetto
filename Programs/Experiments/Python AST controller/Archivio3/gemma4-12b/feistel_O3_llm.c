#include <stdio.h>
#include <stdint.h>

int main(void) {
    printf("Originale: %08X %08X\n", 0xdeadbeef, 0xcafebabe);
    printf("Cifrato:   %08X %08X\n", 0x9dee733b, 0xc7802f9d);
    return 0;
}
