#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

// Struct for a tree node
struct node {
    int key;
    struct node *left;
    struct node *right;
};

// Function to create a new node
struct node *newNode(int item) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a new node with a given key in BST
struct node *insert(struct node *node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}

// Function to do inorder traversal of BST
void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Function to search a given key in BST
struct node *search(struct node *root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (root->key < key)
        return search(root->right, key);
    return search(root->left, key);
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_string>\\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    int len = strlen(input);

    struct node *root = NULL;
    int i = 0;
    while(i < len) {
        int val = 0;
        sscanf(input + i, "%d", &val);
        if (i == 0) {
            root = insert(root, val);
        } else {
            insert(root, val);
        }

        while (input[i] >= '0' && input[i] <= '9') {
            i++;
        }
        i++;
    }

    printf("Inorder traversal of the given tree \\n");
    inorder(root);
    printf("\\n");

    int key_to_search = 40;
    if (search(root, key_to_search) != NULL) {
        printf("%d found in the tree.\\n", key_to_search);
    } else {
        printf("%d not found in the tree.\\n", key_to_search);
    }

    return 0;
}
