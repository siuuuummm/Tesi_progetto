#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**
 * Reconstructed from stripped binary.
 * Function FUN_004004b6
 */
char *register_name(char *name) {
    size_t len = strlen(name);
    char *dest = (char *)0;
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        if (dest != NULL) {
            strcpy(dest, name);
        }
    }
    return dest;
}

/**
 * Reconstructed from stripped binary.
 * Function FUN_004004f1 (main)
 */
int main(int argc, char **argv) {
    char *name;
    char *registered_name;
    size_t name_len;
    char **argv_ptr;

    setvbuf(stdout, (char *)0, 2, 0);
    if (argc > 1) {
        argv_ptr = argv + 1;
        do {
            name = *argv_ptr;
            registered_name = register_name(name);
            if (registered_name == (char *)0) {
                name_len = strlen(name);
                printf("Nome troppo lungo: %zu caratteri\n", name_len);
            } else {
                name_len = strlen(registered_name);
                printf("Registrato: %s (%zu caratteri)\n", registered_name, name_len);
                free(registered_name);
            }
            argv_ptr++;
        } while (argv_ptr != (char **)((char *)argv + 0x10 + (uint64_t)(argc - 2) * 8));
    }
    return 0;
}
