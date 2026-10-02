#include <stdio.h>
#include <stdlib.h>

// Definizione della struttura del nodo dell'albero
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Funzione per creare un nuovo nodo
struct Node* create_node(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        // Gestione dell'errore di allocazione della memoria
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Funzione per inserire un nodo nell'albero
struct Node* insert_node(struct Node* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }
    if (data < root->data) {
        root->left = insert_node(root->left, data);
    } else if (data > root->data) {
        root->right = insert_node(root->right, data);
    }
    return root;
}

// Funzione per calcolare l'altezza dell'albero
int get_height(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    int left_height = get_height(root->left);
    int right_height = get_height(root->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

// Funzione per contare il numero di nodi nell'albero
int count_nodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

// Funzione per la visita inorder dell'albero
void inorder_traversal(struct Node* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

// Funzione per liberare la memoria dell'albero
void free_tree(struct Node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    int num_keys = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < num_keys; i++) {
        root = insert_node(root, keys[i]);
    }

    printf("Visita inorder: ");
    inorder_traversal(root);
    printf("\n");

    printf("Altezza: %d\n", get_height(root));
    printf("Numero nodi: %d\n", count_nodes(root));

    free_tree(root);

    return 0;
}
