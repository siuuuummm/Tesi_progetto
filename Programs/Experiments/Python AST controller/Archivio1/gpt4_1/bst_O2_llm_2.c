#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for the binary search tree
typedef struct node_t {
    int data;
    struct node_t *left;
    struct node_t *right;
} node_t;

// Function to create a new node
node_t *create_node(int data) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Function to insert a node into the BST
node_t *insert_node(node_t *root, int data) {
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

// Function to search for a node in the BST
node_t *search_node(node_t *root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return search_node(root->left, data);
    }
    return search_node(root->right, data);
}

// Function to find the minimum value node in a BST (used for deletion)
node_t *find_min(node_t *node) {
    node_t *current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a node from the BST
node_t *delete_node(node_t *root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = delete_node(root->left, data);
    } else if (data > root->data) {
        root->right = delete_node(root->right, data);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            node_t *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            node_t *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        node_t *temp = find_min(root->right);

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = delete_node(root->right, temp->data);
    }
    return root;
}

// Function to print the tree in-order
void print_tree(node_t *root) {
    if (root != NULL) {
        print_tree(root->left);
        printf("%d ", root->data);
        print_tree(root->right);
    }
}

// Function to free the entire tree
void free_tree(node_t *root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <comma_separated_integers>\n", argv[0]);
        return 1;
    }

    node_t *root = NULL;
    char *token;
    char *input_string = argv[1];

    // Insert nodes from comma-separated string
    token = strtok(input_string, ",");
    while (token != NULL) {
        root = insert_node(root, atoi(token));
        token = strtok(NULL, ",");
    }

    printf("In-order traversal: ");
    print_tree(root);
    printf("\n");

    // Example of searching and deleting
    printf("Searching for 5: %s\n", search_node(root, 5) ? "Found" : "Not Found");
    printf("Deleting 5...\n");
    root = delete_node(root, 5);
    printf("In-order traversal after deleting 5: ");
    print_tree(root);
    printf("\n");

    free_tree(root);

    return 0;
}
