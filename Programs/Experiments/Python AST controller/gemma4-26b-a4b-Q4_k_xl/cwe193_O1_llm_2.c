#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *register_name(char *name) {
    size_t len;
    char *dest;

    len = strlen(name);
    dest = (char *)0x0;
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, name);
    }
    return dest;
}

int main(int argc, char **argv) {
    char *name;
    char *registered_name;
    size_t len;
    char **argv_ptr;

    setvbuf(stdout, (char *)0x0, 2, 0);
    if (argc > 1) {
        argv_ptr = (char **)((uintptr_t)argv + 8);
        do {
            name = *argv_ptr;
            registered_name = register_name(name);
            if (registered_name == (char *)0x0) {
                len = strlen(name);
                printf("Nome troppo lungo: %zu caratteri\n", len);
            } else {
                len = strlen(registered_name);
                printf("Registrato: %s (%zu caratteri)\n", registered_name, len);
                free(registered_name);
            }
            argv_ptr++;
        } while ((uintptr_t)argv_ptr != ((uintptr_t)argv + 0x10 + (uint64_t)(argc - 2) * 8));
    }
    return 0;
}
