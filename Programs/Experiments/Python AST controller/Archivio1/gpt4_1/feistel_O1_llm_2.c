#include <stdio.h>
#include <stdint.h>

// Rotational XOR encryption primitive
uint encrypt_block(uint data, int key) {
    return ((data << 5) | (data >> 27)) ^ (key + 0x9e3779b9U);
}

// Simple block cipher: chained enc + rotation
void encrypt_data(uint32_t *data1, uint32_t *data2, int key) {
    uint32_t tmp;
    uint32_t round_key = key + 0x9e3779b9U;
    do {
        tmp = *data1;
        *data1 = ((tmp << 5) | (tmp >> 27)) ^ (*data2) ^ round_key;
        *data2 = tmp;
        round_key++;
    } while (round_key != key + 0x9e3779c1U);
}

int main(void) {
    uint32_t data1 = 0xdeadbeef;
    uint32_t data2 = 0xcafebabe;
    printf("Originale: %08X %08X\n", data1, data2);
    encrypt_data(&data1, &data2, 0x12345678);
    printf("Cifrato:   %08X %08X\n", data1, data2);
    return 0;
}
