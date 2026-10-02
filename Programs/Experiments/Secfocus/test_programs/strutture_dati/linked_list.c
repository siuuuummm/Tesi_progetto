/* linked_list.c — Difficolta: MEDIA
 * Lista concatenata con malloc/free. Le struct e i puntatori a struct
 * sono persi nella compilazione: ottimo test per il recupero dei tipi user-defined. */
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

struct Node *push_front(struct Node *head, int value) {
    struct Node *n = malloc(sizeof(struct Node));
    n->value = value;
    n->next = head;
    return n;
}

int list_length(struct Node *head) {
    int count = 0;
    for (struct Node *p = head; p != NULL; p = p->next)
        count++;
    return count;
}

int list_sum(struct Node *head) {
    int sum = 0;
    for (struct Node *p = head; p != NULL; p = p->next)
        sum += p->value;
    return sum;
}

void list_free(struct Node *head) {
    while (head) {
        struct Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    struct Node *list = NULL;
    for (int i = 1; i <= 5; i++)
        list = push_front(list, i * 10);

    printf("Lunghezza: %d\n", list_length(list));
    printf("Somma: %d\n", list_sum(list));

    for (struct Node *p = list; p; p = p->next)
        printf("%d ", p->value);
    printf("\n");

    list_free(list);
    return 0;
}
