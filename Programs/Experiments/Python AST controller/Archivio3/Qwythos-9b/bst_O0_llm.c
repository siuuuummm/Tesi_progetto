#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int32_t root(int32_t val) {
    int32_t *node;
    node = malloc(8);
    *node = val;
    *(uint8_t *)(node + 2) = 0;
    *(uint8_t *)(node + 4) = 0;
    return node;
}

int32_t *insert(int32_t *node, int32_t val) {
    int32_t *uVar1;
    if (node == NULL) {
        node = root(val);
    } else if (val < *node) {
        uVar1 = insert(*(int32_t **)(node + 2), val);
        *(int32_t **)(node + 2) = uVar1;
    } else if (*node < val) {
        uVar1 = insert(*(int32_t **)(node + 4), val);
        *(int32_t **)(node + 4) = uVar1;
    }
    return node;
}

void print_inorder(uint32_t *node) {
    if (node != NULL) {
        print_inorder(*(uint32_t **)(node + 2));
        printf("%d ", node[0]);
        print_inorder(*(uint32_t **)(node + 4));
    }
}

void free_tree(void *node) {
    if (node != NULL) {
        free_tree(*(uint8_t **)((uint64_t)node + 8));
        free_tree(*(uint8_t **)((uint64_t)node + 16));
        free(node);
    }
}

int32_t height(uint32_t *node) {
    int32_t h1, h2;
    if (node == NULL) {
        return 0;
    } else {
        h1 = height(*(uint8_t **)(node + 8));
        h2 = height(*(uint8_t **)(node + 16));
        if (h1 <= h2) {
            h1 = h2;
        }
        h1 = h1 + 1;
    }
    return h1;
}

int32_t count(uint32_t *node) {
    int32_t c1, c2;
    if (node == NULL) {
        return 0;
    } else {
        c1 = count(*(uint8_t **)(node + 8));
        c2 = count(*(uint8_t **)(node + 16));
        c2 = c2 + c1 + 1;
    }
    return c2;
}

int32_t main(void) {
    uint8_t seed[8];
    seed[0] = 0x32;
    seed[1] = 0x1e;
    seed[2] = 0x46;
    seed[3] = 0x14;
    seed[4] = 0x28;
    seed[5] = 0x3c;
    seed[6] = 0x50;
    seed[7] = 0;
    int32_t root_node = 0;
    for (int i = 0; i < 7; i++) {
        root_node = insert(root_node, seed[i]);
    }
    printf("Visita inorder: ");
    print_inorder(root_node);
    putchar(10);
    uint32_t h = height(root_node);
    printf("Altezza: %d\n", h);
    uint32_t n = count(root_node);
    printf("Numero nodi: %d\n", n);
    free_tree(root_node);
    return 0;
}
