#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the binary search tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node (corresponds to FUN_00400496)
struct Node* create_node(int data) {
    // sizeof(struct Node) is 24 bytes (int: 4, pointer: 8, pointer: 8, with padding)
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Function to insert a node into the BST (corresponds to FUN_004004d6)
struct Node* insert_node(struct Node* node, int data) {
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

// Function to calculate the height of the tree (corresponds to FUN_00400550)
int calculate_height(struct Node* node) {
    if (node == NULL) {
        return 0;
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

// Function to count the total number of nodes (corresponds to FUN_004005a0)
int count_nodes(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

// Function to perform inorder traversal and print nodes (corresponds to FUN_004005e6)
void inorder_traversal(struct Node* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

// Function to free the entire tree (corresponds to FUN_00400635)
void free_tree(struct Node* node) {
    if (node != NULL) {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
    }
}

// Main function (corresponds to FUN_00400679)
int main(void) {
    int data[] = {50, 30, 70, 20, 40, 60, 80};
    int num_elements = sizeof(data) / sizeof(data[0]);
    struct Node* root = NULL;

    for (int i = 0; i < num_elements; i++) {
        root = insert_node(root, data[i]);
    }

    printf("Visita inorder: ");
    inorder_traversal(root);
    printf("\n");

    int height = calculate_height(root);
    printf("Altezza: %d\n", height);

    int total_nodes = count_nodes(root);
    printf("Numero nodi: %d\n", total_nodes);

    free_tree(root);

    return 0;
}
