#include <stdio.h>
#include <stdint.h>

void tea_encrypt(uint32_t *value, int *key) {
    uint32_t v0 = value[0];
    uint32_t v1 = value[1];
    int sum = 0;
    do {
        sum -= 0x61c88647;
        v0 += (v1 * 0x10 + key[0] ^ (v1 >> 5) + key[1] ^ sum + v1);
        v1 += (v0 * 0x10 + key[2] ^ (v0 >> 5) + key[3] ^ sum + v0);
    } while (sum != -0x3910c8e0);
    value[0] = v0;
    value[1] = v1;
}

void tea_decrypt(uint32_t *value, int *key) {
    uint32_t v0 = value[0];
    uint32_t v1 = value[1];
    int sum = -0x3910c8e0;
    do {
        v1 -= (v0 * 0x10 + key[2] ^ (v0 >> 5) + key[3] ^ v0 + sum);
        v0 -= (v1 * 0x10 + key[0] ^ (v1 >> 5) + key[1] ^ v1 + sum);
        sum += 0x61c88647;
    } while (sum != 0);
    value[0] = v0;
    value[1] = v1;
}

int main() {
    // Le costanti sono placeholder presi dalla disasm -- dati globali e costanti con nomi ragionevoli
    uint64_t key_data = 0; // Sostituire con _DAT_004011e0/_UNK_004011e8 se noti
    int key[4] = {0, 0, 0, 0}; // Sostituire se noti
    
    printf("Originale: %08X %08X\n", 0x12345678, 0x9abcdef0);

    uint64_t value = 0; // Sostituire con DAT_004011f0 se noti
    tea_encrypt((uint32_t *)&value, key);
    printf("Cifrato:   %08X %08X\n", (uint32_t)value, (uint32_t)(value >> 32));
    tea_decrypt((uint32_t *)&value, key);
    printf("Decifrato: %08X %08X\n", (uint32_t)value, (uint32_t)(value >> 32));
    return 0;
}
