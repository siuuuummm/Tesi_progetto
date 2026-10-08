#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *register_name(char *name) {
    size_t len = strlen(name);
    char *dest;

    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        if (dest != NULL) {
            strcpy(dest, name);
        }
    } else {
        dest = (char *)0x0;
    }
    return dest;
}

int main(int argc, char **argv) {
    char *name_ptr;
    size_t name_len;
    int i;

    setvbuf(stdout, NULL, 2, 0);

    for (i = 1; i < argc; i++) {
        name_ptr = register_name(argv[i]);
        if (name_ptr == (char *)0x0) {
            name_len = strlen(argv[i]);
            printf("Nome troppo lungo: %zu caratteri\n", name_len);
        } else {
            name_len = strlen(name_ptr);
            printf("Registrato: %s (%zu caratteri)\n", name_ptr, name_len);
            free(name_ptr);
        }
    }

    return 0;
}
