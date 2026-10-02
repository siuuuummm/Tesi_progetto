#include <stdio.h>
#include <stdlib.h>

// Nodo della lista collegata
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Crea un nuovo nodo e lo collega in testa alla lista
Node* create_node(Node* head, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = head;
    return new_node;
}

// Restituisce la lunghezza della lista
int list_length(Node* head) {
    int length = 0;
    Node* curr = head;
    while (curr != NULL) {
        length++;
        curr = curr->next;
    }
    return length;
}

// Restituisce la somma dei valori nella lista
int list_sum(Node* head) {
    int sum = 0;
    Node* curr = head;
    while (curr != NULL) {
        sum += curr->value;
        curr = curr->next;
    }
    return sum;
}

// Libera tutta la memoria allocata dalla lista
void free_list(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
}

// Funzione main decompilata
ing main() {
    Node* head = NULL;
    for (int i = 1; i <= 5; i++) {
        head = create_node(head, i * 10);
    }

    int length = list_length(head);
    printf("Lunghezza: %d\n", length);

    int sum = list_sum(head);
    printf("Somma: %d\n", sum);

    for (Node* curr = head; curr != NULL; curr = curr->next) {
        printf("%d ", curr->value);
    }
    putchar('\n');

    free_list(head);
    return 0;
}
