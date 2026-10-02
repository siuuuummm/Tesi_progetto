#include <stdio.h>
#include <stdlib.h>

struct chain_node {
    unsigned char value;
    char _pad[7];
    struct chain_node *next;
};

// Trasforma ogni nodo della catena secondo una regola dipendente da "mode"
void chain_transform(struct chain_node *node, int mode) {
    unsigned char x;
    while (node != NULL) {
        if (mode == 0) {
            x = (node->value - 1) ^ 0x55;
        } else {
            x = (node->value ^ 0x55) + 1;
        }
        node->value = x;
        node = node->next;
    }
}

int main(void) {
    // Alloca due nodi da 16 byte l'uno
    struct chain_node *head = (struct chain_node*)malloc(sizeof(struct chain_node));
    head->value = 0xba;
    head->next = (struct chain_node*)malloc(sizeof(struct chain_node));
    head->next->value = 0x8a;
    head->next->next = NULL;

    // Trasforma la catena con "mode=1"
    chain_transform(head, 1);

    if ((head->next->value >> 4) == (head->value & 0xF)) {
        puts("System stable.");
    } else {
        puts("Integrity check failed.");
    }

    // Libera la catena
    struct chain_node *tmp;
    while (head != NULL) {
        tmp = head->next;
        free(head);
        head = tmp;
    }

    return 0;
}
