#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Processa una "catena" di strutture di memoria con operazioni bitwise/arithmetiche
typedef struct ChainNode {
    uint8_t value;
    struct ChainNode* next;
} ChainNode;

// Modifica la catena secondo un algoritmo specifico
// Se mode == 0: value = (value - 1) ^ 0x55
// Se mode == 1: value = (value ^ 0x55) + 1
void process_chain(ChainNode* head, int mode) {
    for (ChainNode* node = head; node != NULL; node = node->next) {
        if (mode == 0) {
            node->value = (uint8_t)((node->value - 1) ^ 0x55);
        } else {
            node->value = (uint8_t)((node->value ^ 0x55) + 1);
        }
    }
}

int main(void) {
    // Alloca il primo elemento della catena
    ChainNode* first = (ChainNode*)malloc(sizeof(ChainNode));
    if (!first) return 1;
    first->value = 0xBA;

    // Alloca il secondo elemento e concatena
    ChainNode* second = (ChainNode*)malloc(sizeof(ChainNode));
    if (!second) { free(first); return 1; }
    first->next = second;
    second->value = 0x8A;
    second->next = NULL;

    // Il campo next del secondo node viene azzerato di nuovo per chiarezza
    // (rispecchia *(undefined8 *)(*(long *)(local_10 + 8) + 8) = 0;)
    // Ma è già NULL per la struct.

    process_chain(first, 1);

    if ((first->value & 0xF) == (second->value >> 4)) {
        puts("System stable.");
    } else {
        puts("Integrity check failed.");
    }
    // Libera la catena
    ChainNode* iter = first;
    while (iter != NULL) {
        ChainNode* tmp = iter->next;
        free(iter);
        iter = tmp;
    }
    return 0;
}
