#include <stdio.h>
#include <stdlib.h>

// Nodo della lista collegata
struct Node {
    int value;
    struct Node* next;
};

// Crea un nuovo nodo e lo aggiunge in testa
struct Node* create_node(struct Node* head, int value) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (!new_node) return NULL;
    new_node->value = value;
    new_node->next = head;
    return new_node;
}

// Conta i nodi nella lista
int list_length(struct Node* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// Somma i valori di tutti i nodi
int list_sum(struct Node* head) {
    int sum = 0;
    while (head != NULL) {
        sum += head->value;
        head = head->next;
    }
    return sum;
}

// Libera la memoria della lista
void free_list(struct Node* head) {
    struct Node* tmp;
    while (head != NULL) {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}

int main() {
    struct Node* head = NULL;
    int value = 10;
    while (value != 60) {
        head = create_node(head, value);
        value += 10;
    }
    printf("Lunghezza: %d\n", list_length(head));
    printf("Somma: %d\n", list_sum(head));

    for (struct Node* curr = head; curr != NULL; curr = curr->next) {
        printf("%d ", curr->value);
    }
    putchar('\n');
    free_list(head);
    return 0;
}
