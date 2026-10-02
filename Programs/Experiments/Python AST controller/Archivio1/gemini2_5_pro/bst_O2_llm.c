#include <stdio.h>
#include <stdlib.h>

// Definizione della struttura per un nodo dell'albero binario di ricerca
typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Funzione per creare e inserire un nuovo nodo nel BST
TreeNode* insert_node(TreeNode* root, int value) {
    if (root == NULL) {
        TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
        if (new_node == NULL) {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    if (value < root->value) {
        root->left = insert_node(root->left, value);
    } else if (value > root->value) {
        root->right = insert_node(root->right, value);
    }
    return root;
}

// Funzione per la visita inorder dell'albero (stampa i nodi in ordine crescente)
void inorder_traversal(TreeNode* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->value);
        inorder_traversal(root->right);
    }
}

// Funzione per calcolare l'altezza di un albero
int calculate_height(TreeNode* root) {
    if (root == NULL) {
        return -1; // Altezza di un albero vuoto è -1
    }
    int left_height = calculate_height(root->left);
    int right_height = calculate_height(root->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

// Funzione per contare il numero di nodi in un albero
int count_nodes(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

// Funzione per deallocare la memoria dell'intero albero
void free_tree(TreeNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main(void) {
    // Array di valori iniziali da inserire nell'albero
    int initial_values[] = {70, 10, 90, 30, 80, 5, 20, 40, 60, 100};
    int num_values = sizeof(initial_values) / sizeof(initial_values[0]);

    // La radice dell'albero parte da 50
    TreeNode* root = insert_node(NULL, 50);

    // Inserisce i valori dall'array nell'albero
    for (int i = 0; i < num_values; ++i) {
        root = insert_node(root, initial_values[i]);
    }

    // Stampa la visita inorder
    printf("Visita inorder: ");
    inorder_traversal(root);
    putchar('\n');

    // Calcola e stampa l'altezza dell'albero
    int height = calculate_height(root);
    printf("Altezza: %d\n", height);

    // Conta e stampa il numero totale di nodi
    int nodes_count = count_nodes(root);
    printf("Numero nodi: %d\n", nodes_count);

    // Libera la memoria allocata per l'albero
    free_tree(root);

    return 0;
}
