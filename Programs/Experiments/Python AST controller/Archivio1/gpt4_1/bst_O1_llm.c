#include <stdio.h>
#include <stdlib.h>

// Nodo dell'albero binario di ricerca
typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

// Crea un nuovo nodo
Node* create_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Inserisce un valore nell'albero
Node* insert(Node* root, int value) {
    if (root == NULL) {
        return create_node(value);
    } else if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    }
    return root;
}

// Calcola l'altezza dell'albero
int tree_height(Node* root) {
    if (root) {
        int h_left = tree_height(root->left);
        int h_right = tree_height(root->right);
        return (h_left > h_right ? h_left : h_right) + 1;
    }
    return 0;
}

// Conta nodi nell'albero
int count_nodes(Node* root) {
    if (root) {
        return count_nodes(root->left) + 1 + count_nodes(root->right);
    }
    return 0;
}

// Visita inorder
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

// Libera l'albero
void free_bst(Node* root) {
    if (root) {
        free_bst(root->left);
        free_bst(root->right);
        free(root);
    }
}

int main(void) {
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    Node* root = NULL;
    for (int i = 0; i < 7; ++i) {
        root = insert(root, values[i]);
    }
    printf("Visita inorder: ");
    inorder(root);
    putchar('\n');
    printf("Altezza: %d\n", tree_height(root));
    printf("Numero nodi: %d\n", count_nodes(root));
    free_bst(root);
    return 0;
}
