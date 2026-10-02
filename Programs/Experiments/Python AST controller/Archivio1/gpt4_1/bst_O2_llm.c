#include <stdio.h>
#include <stdlib.h>

// Nodo di un albero binario di ricerca
// Gli offset negli accessi ai puntatori (
//   +8, +0x10, ecc) fanno supporre una struttura del tipo:
typedef struct Node {
    int valore;
    struct Node *sinistra;
    struct Node *destra;
} Node;

// Costruisce (o aggiorna) l'albero con un nuovo valore
Node* inserisci(Node* radice, int valore) {
    if (radice == NULL) {
        Node* nuovo = (Node*)malloc(sizeof(Node));
        nuovo->valore = valore;
        nuovo->sinistra = NULL;
        nuovo->destra = NULL;
        return nuovo;
    }
    if (valore < radice->valore) {
        radice->sinistra = inserisci(radice->sinistra, valore);
    } else if (valore > radice->valore) {
        radice->destra = inserisci(radice->destra, valore);
    }
    return radice;
}

// Visita inorder ricorsiva
void visita_inorder(Node *radice) {
    if (radice != NULL) {
        visita_inorder(radice->sinistra);
        printf("%d ", radice->valore);
        visita_inorder(radice->destra);
    }
}

// Calcola l'altezza dell'albero
int altezza(Node *radice) {
    if (radice == NULL) return 0;
    int h_sx = altezza(radice->sinistra);
    int h_dx = altezza(radice->destra);
    return (h_sx > h_dx ? h_sx : h_dx) + 1;
}

// Conta ricorsivamente tutti i nodi dell'albero
int conta_nodi(Node *radice) {
    if (radice == NULL) return 0;
    return 1 + conta_nodi(radice->sinistra) + conta_nodi(radice->destra);
}

// Dealloca ricorsivamente l'intero albero
void libera_albero(Node *radice) {
    if (radice != NULL) {
        libera_albero(radice->sinistra);
        libera_albero(radice->destra);
        free(radice);
    }
}

// Funzione main ricostruita basata su entry e FUN_004003b0
int main(void) {
    Node *root = NULL;
    int x;
    while (scanf("%d", &x) == 1) {
        root = inserisci(root, x);
    }
    printf("Visita inorder: ");
    visita_inorder(root);
    putchar('\n');
    printf("Altezza: %d\n", altezza(root));
    printf("Numero nodi: %d\n", conta_nodi(root));
    libera_albero(root);
    return 0;
}
