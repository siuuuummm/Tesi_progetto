#include <stdio.h>
#include <stdint.h>

// Istruzioni: (cmd, val)
uint8_t instructions[] = {
    0x02, 0x00,
    0x3e, 0x00,
    0x01, 0x00,
    0x00, 0x00
};

void process_instructions() {
    uint8_t result = 0x42;
    uint8_t *pc = instructions;

    while (pc < instructions + sizeof(instructions)) {
        uint8_t cmd = *pc;
        uint8_t val = *(pc + 1);

        if (cmd == 0x02) {
            result = result + val;
        } else if (cmd == 0x03) {
            result = (result << (val & 7)) | (result >> (8 - (val & 7)));
        } else if (cmd == 0x01) {
            result = result ^ val;
        } else { // Non riconosciuto, termina
            break;
        }
        pc += 2;
    }
    printf("Risultato finale: 0x%02X\n", result);
}

int main() {
    process_instructions();
    return 0;
}
