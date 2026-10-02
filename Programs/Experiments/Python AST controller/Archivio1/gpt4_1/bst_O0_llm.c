#include <stdio.h>
#include <stdlib.h>

// Struttura nodo BST
struct BSTNode {
    int value;
    struct BSTNode *left;
    struct BSTNode *right;
};

typedef struct BSTNode BSTNode;

// Crea un nuovo nodo
BSTNode* bst_create_node(int value) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Inserisce un valore nel BST
BSTNode* bst_insert(BSTNode* root, int value) {
    if (root == NULL) {
        return bst_create_node(value);
    } else if (value < root->value) {
        root->left = bst_insert(root->left, value);
    } else if (value > root->value) {
        root->right = bst_insert(root->right, value);
    }
    return root;
}

// Calcola l'altezza del BST
int bst_height(BSTNode* root) {
    if (root == NULL) return 0;
    int lh = bst_height(root->left);
    int rh = bst_height(root->right);
    return (lh > rh ? lh : rh) + 1;
}

// Conta il numero di nodi nel BST
int bst_count(BSTNode* root) {
    if (root == NULL) return 0;
    return 1 + bst_count(root->left) + bst_count(root->right);
}

// Visita inorder e stampa valori
void bst_print_inorder(BSTNode* root) {
    if (root) {
        bst_print_inorder(root->left);
        printf("%d ", root->value);
        bst_print_inorder(root->right);
    }
}

// Dealloca tutto il BST
void bst_free(BSTNode* root) {
    if (root) {
        bst_free(root->left);
        bst_free(root->right);
        free(root);
    }
}

int main(void) {
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = 7;
    BSTNode* root = NULL;
    for (int i = 0; i < n; ++i) {
        root = bst_insert(root, values[i]);
    }
    printf("Visita inorder: ");
    bst_print_inorder(root);
    putchar('\n');
    printf("Altezza: %d\n", bst_height(root));
    printf("Numero nodi: %d\n", bst_count(root));
    bst_free(root);
    return 0;
}
