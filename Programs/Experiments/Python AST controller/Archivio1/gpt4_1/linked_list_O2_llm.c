#include <stdio.h>
#include <stdlib.h>

// Nodo della lista collegata
typedef struct Node {
    int value;
    struct Node *next;
} Node;

// Crea e aggiunge un nodo all'inizio della lista
Node* insert_front(Node* head, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = head;
    return new_node;
}

// Conta il numero di nodi della lista
int list_length(Node* head) {
    int length = 0;
    while (head) {
        length++;
        head = head->next;
    }
    return length;
}

// Calcola la somma dei valori dei nodi
int list_sum(Node* head) {
    int sum = 0;
    while (head) {
        sum += head->value;
        head = head->next;
    }
    return sum;
}

// Stampa tutti i valori della lista
void print_list(Node* head) {
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    putchar('\n');
}

// Libera tutta la memoria occupata dalla lista
void free_list(Node* head) {
    Node* tmp;
    while (head) {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}

int main(void) {
    Node *list = NULL;
    int value;
    // Inserisce: 10, 20, 30, 40, 50 (in testa, invertito)
    for (value = 10; value < 60; value += 10) {
        list = insert_front(list, value);
    }

    printf("Lunghezza: %d\n", list_length(list));
    printf("Somma: %d\n", list_sum(list));
    print_list(list);
    free_list(list);
    return 0;
}
