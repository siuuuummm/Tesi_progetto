#include <stdio.h>
#include <stdint.h>

// Constants identified from the binary
const uint32_t DELTA = 0x61c88647;
const uint32_t MAX_ROUNDS = 0x3910c8e0;

// Note: In the decompilation, the loop condition for encryption was:
// iVar3 = iVar3 + -0x61c88647;
// do { ... } while (iVar3 != -0x3910c8e0);
// Since iVar3 starts at 0, it counts down. 
// However, iVar3 - 0x61c88647 is effectively iVar3 + (uint32_t)-0x61c88647.
// To be faithful to the binary's behavior:

void encrypt(uint32_t *data, uint32_t *key) {
    uint32_t uVar1 = data[0];
    uint32_t uVar2 = data[1];
    int32_t iVar3 = 0;
    
    do {
        iVar3 = iVar3 - DELTA;
        uVar1 = uVar1 + (uVar2 * 0x10 + (key[0] ^ (uVar2 >> 5)) + key[1] ^ iVar3 + uVar2);
        uVar2 = uVar2 + (uVar1 * 0x10 + key[2] ^ (uVar1 >> 5) + key[3] ^ iVar3 + uVar1);
    } while (iVar3 != (int32_t)-0x3910c8e0);
    
    data[0] = uVar1;
    data[1] = uVar2;
}

void decrypt(uint32_t *data, uint32_t *key) {
    uint32_t uVar1 = data[0];
    uint32_t uVar2 = data[1];
    int32_t iVar3 = (int32_t)-0x3910c8e0;
    
    do {
        uVar2 = uVar2 - (uVar1 * 0x10 + key[2] ^ (uVar1 >> 5) + key[3] ^ uVar1 + iVar3);
        uVar1 = uVar1 - (uVar2 * 0x10 + key[0] ^ (uVar2 >> 5) + key[1] ^ uVar2 + iVar3);
        iVar3 = iVar3 + DELTA;
    } while (iVar3 != 0);
    
    data[0] = uVar1;
    data[1] = uVar2;
}

int main(void) {
    // Values from _DAT_004011e0 and _UNK_004011e8 
    // and _DAT_004011f0 are extracted via the logic in the decompiled main.
    // The decompiled main shows:
    // local_18 = _DAT_004011e0;
    // uStack_10 = _UNK_004011e8;
    // printf("Originale: %08X %08X\n", 0x12345678, 0x9abcdef0);
    // local_20 = DAT_004011f0;
    
    // Since I cannot see the raw hex of the data labels directly without more tools,
    // but the instructions say to produce the code and the main logic.
    // I will represent the data labels as constants as they appear in the decompilation flow.
    
    uint32_t key[4] = {0x11111111, 0x22222222, 0x33333333, 0x44444444}; // Placeholder for actual values if found
    // However, the prompt says: "Riproduci ESATTAMENTE i valori numerici che leggi nel decompilato".
    // The decompilation of main showed hardcoded values in printf.
    
    // Let's look at the decompiled main again.
    // local_18 = _DAT_004011e0;
    // uStack_10 = _UNK_004011e8;
    // printf("Originale: %08X %08X\n",0x12345678,0x9abcdef0);
    // local_20 = DAT_004011f0;
    // FUN_00400500(&local_20,&local_18);
    // printf("Cifrato:   %08X %08X\n",local_20 & 0xffffffff,local_20 >> 0x20);
    // FUN_00400590(&local_20,&local_18);
    // printf("Decifrato: %08X %08X\n",local_20 & 0xffffffff,local_20 >> 0x20);

    // I will use the labels as variables and assume the values are accessible.
    // Since I need a "compilable" file, I must provide values for the labels.
    // I will use the values from the printfs where applicable.
    
    uint32_t data[2] = {0x12345678, 0x9abcdef0}; // From the first printf
    uint32_t key_vals[4] = {0x12345678, 0x9abcdef0, 0x12345678, 0x9abcdef0}; // Example
    
    // Re-evaluating the decompilation of main:
    // local_18 is passed to FUN_00400500 as param_2 (the key).
    // local_20 is passed to FUN_00400500 as param_1 (the data).
    
    // I will use 0x12345678 and 0x9abcdef0 as the data.
    // I need to find the values of _DAT_004011e0, _UNK_004011e8, and _DAT_004011f0.
    // I'll check list_data_items.
}
