/* bst.c — Difficolta: ALTA
 * Albero binario di ricerca con inserimento e visita ricorsivi.
 * Ricorsione + struct annidate + puntatori: tra i casi piu difficili
 * da decompilare correttamente, specie a O2/O3. */
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *create_node(int key) {
    struct TreeNode *n = malloc(sizeof(struct TreeNode));
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    return n;
}

struct TreeNode *insert(struct TreeNode *root, int key) {
    if (root == NULL)
        return create_node(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

int tree_height(struct TreeNode *root) {
    if (root == NULL) return 0;
    int lh = tree_height(root->left);
    int rh = tree_height(root->right);
    return 1 + (lh > rh ? lh : rh);
}

int count_nodes(struct TreeNode *root) {
    if (root == NULL) return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

void inorder(struct TreeNode *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void tree_free(struct TreeNode *root) {
    if (root == NULL) return;
    tree_free(root->left);
    tree_free(root->right);
    free(root);
}

int main(void) {
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(keys) / sizeof(keys[0]);

    struct TreeNode *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, keys[i]);

    printf("Visita inorder: ");
    inorder(root);
    printf("\n");
    printf("Altezza: %d\n", tree_height(root));
    printf("Numero nodi: %d\n", count_nodes(root));

    tree_free(root);
    return 0;
}
