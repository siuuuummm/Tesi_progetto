#include <stdio.h>
#include <stdlib.h>

unsigned char program[] = {1, 0xAA, 2, 0x05, 3, 0x01, 1, 0x55};

int main() {
    unsigned char reg = 0x42;
    int pc = 0;
    int x = 10;
    int y = 20;
    if ((x * x + y * y) >= 0) { 
        while (pc < sizeof(program)) {
            unsigned char op = program[pc++];
            unsigned char val = program[pc++];

            switch (op) {
                case 1: reg ^= val; break;
                case 2: reg += val; break;
                case 3: reg = (reg << val) | (reg >> (8 - val)); break;
                default: goto end;
            }
        }
    }

end:
    printf("Risultato finale: 0x%02X\n", reg);
    return 0;
}
