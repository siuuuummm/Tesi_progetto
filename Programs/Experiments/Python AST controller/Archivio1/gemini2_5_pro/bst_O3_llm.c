#include <stdio.h>
#include <stdlib.h>

// Definizione della struttura per un nodo dell'albero binario di ricerca
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Prototipi delle funzioni
struct TreeNode* insert_node(struct TreeNode* node, int data);
void inorder_traversal(struct TreeNode* root);
int calculate_height(struct TreeNode* node);
int count_nodes(struct TreeNode* node);
void free_tree(struct TreeNode* node);
struct TreeNode* create_node(int data);

// Funzione per creare un nuovo nodo
struct TreeNode* create_node(int data) {
    struct TreeNode* new_node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (new_node == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Funzione per inserire un nodo nell'albero
struct TreeNode* insert_node(struct TreeNode* node, int data) {
    if (node == NULL) {
        return create_node(data);
    }

    if (data < node->data) {
        node->left = insert_node(node->left, data);
    } else if (data > node->data) {
        node->right = insert_node(node->right, data);
    }

    return node;
}

// Funzione per la visita inorder dell'albero
void inorder_traversal(struct TreeNode* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

// Funzione per calcolare l'altezza dell'albero
int calculate_height(struct TreeNode* node) {
    if (node == NULL) {
        return -1; // Altezza di un albero vuoto è -1
    } else {
        int left_height = calculate_height(node->left);
        int right_height = calculate_height(node->right);

        if (left_height > right_height) {
            return left_height + 1;
        } else {
            return right_height + 1;
        }
    }
}

// Funzione per contare i nodi dell'albero
int count_nodes(struct TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

// Funzione per liberare la memoria dell'albero
void free_tree(struct TreeNode* node) {
    if (node != NULL) {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
    }
}

// Funzione principale
int main() {
    struct TreeNode* root = create_node(50);

    // Array di valori da inserire nell'albero
    int values_to_insert[] = {30, 70, 20, 40, 60, 80, 15, 25, 35, 45, 55, 65, 75, 85};
    int num_values = sizeof(values_to_insert) / sizeof(values_to_insert[0]);

    for (int i = 0; i < num_values; ++i) {
        insert_node(root, values_to_insert[i]);
    }

    printf("Visita inorder: ");
    inorder_traversal(root);
    printf("\n");

    int height = calculate_height(root);
    printf("Altezza: %d\n", height);

    int total_nodes = count_nodes(root);
    printf("Numero nodi: %d\n", total_nodes);

    // Liberare la memoria allocata per l'albero
    free_tree(root);

    return 0;
}
