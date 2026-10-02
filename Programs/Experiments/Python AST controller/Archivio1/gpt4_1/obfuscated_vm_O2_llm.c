#include <stdio.h>
#include <stdint.h>

// Funzione principale
int main(void) {
    char instruction;
    unsigned char value;
    unsigned char reg = 0x42;
    unsigned char *pc = (unsigned char *)"\x01\x10\x02\x05\x03\x03\x01\x1f\x00\x00\x00\x00\x00\x00\x00\x00";
    unsigned char *end = pc + 8;
    while (pc != end) {
        instruction = *pc;
        value = *(pc + 1);
        if (instruction == 0x02) {
            reg += value;
        } else if (instruction == 0x03) {
            reg = (reg << (value & 7)) | (reg >> (8 - (value & 7)));
        } else {
            if (instruction != 0x01)
                break;
            reg ^= value;
        }
        pc += 2;
    }
    printf("Risultato finale: 0x%02X\n", reg);
    return 0;
}
