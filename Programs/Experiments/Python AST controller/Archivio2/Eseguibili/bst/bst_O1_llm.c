#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *key;
    struct node *left;
    struct node *right;
};

struct node *newNode(char *item) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = strdup(item);
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%s \n", root->key);
        inorder(root->right);
    }
}

struct node *insert(struct node *node, char *key) {
    if (node == NULL) return newNode(key);
    if (strcmp(key, node->key) < 0)
        node->left = insert(node->left, key);
    else if (strcmp(key, node->key) > 0)
        node->right = insert(node->right, key);
    return node;
}

struct node *search(struct node *root, char *key) {
    if (root == NULL || strcmp(root->key, key) == 0)
       return root;
    if (strcmp(root->key, key) < 0)
       return search(root->right, key);
    return search(root->left, key);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string1> <string2> ...\n", argv[0]);
        return 1;
    }
    struct node *root = NULL;
    root = insert(root, argv[1]);
    for (int i = 2; i < argc; i++) {
        insert(root, argv[i]);
    }
    printf("Inorder traversal of the given tree \n");
    inorder(root);
    return 0;
}
