#include <stdio.h>
#include <stdlib.h>

#define MAGIC_MASK 0xAA
#define XOR_KEY 0x55

typedef struct Node {
    unsigned char val;
    struct Node* next;
} Node;

void traverse(Node* head, int action) {
    Node* curr = head;
    while (curr != NULL) {
        if (action) {
            curr->val = (curr->val ^ XOR_KEY) + 1;
        } else {
            curr->val = (curr->val - 1) ^ XOR_KEY;
        }
        curr = curr->next;
    }
}

int main() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->val = 0x10 ^ MAGIC_MASK;

    head->next = (Node*)malloc(sizeof(Node));
    head->next->val = 0x20 ^ MAGIC_MASK;
    head->next->next = NULL;

    traverse(head, 1);

    if ((head->val & 0x0F) != (head->next->val >> 4)) {
        printf("Integrity check failed.\n");
    } else {
        printf("System stable.\n");
    }

    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }

    return 0;
}
