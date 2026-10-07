#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/* Internal struct as found in the binary */
typedef struct {
    uint64_t ptr;
    uint64_t children[16];
} __attribute__((packed)) inner_t;

/* Recursive printer: prints a value and its children */
void print_recursive(uint64_t v, const inner_t *parent) {
    /* Recursively process each child */
    for (size_t i = 0; i < 16; i++) {
        uint64_t child = parent->children[i];
        if (child != 0) {
            print_recursive(child, parent);
        }
    }
    /* Print the value */
    printf("%lu ", v);
}

/* Entry point as decompiled */
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <struct_ptr>\n", argv[0]);
        return 1;
    }

    inner_t *head = (inner_t *)strtoul(argv[1], NULL, 0);
    if (head == NULL) {
        fprintf(stderr, "Invalid pointer argument\n");
        return 1;
    }

    /* Recursive walk and print as in the binary */
    for (size_t i = 0; i < 16; i++) {
        uint64_t child = head->children[i];
        if (child != 0) {
            print_recursive(child, head);
        }
    }
    printf("%lu\n", head->ptr);

    free(head);
    return 0;
}
