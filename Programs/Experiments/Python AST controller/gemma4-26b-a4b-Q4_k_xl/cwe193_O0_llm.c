#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *process_name(char *name) {
    size_t len = strlen(name);
    char *dest;
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, name);
    } else {
        dest = (char *)0x0;
    }
    return dest;
}

int main(int argc, char **argv) {
    char *name_copy;
    size_t len;
    int i;

    setvbuf(stdout, NULL, 2, 0);
    for (i = 1; i < argc; i++) {
        name_copy = process_name(argv[i]);
        if (name_copy == NULL) {
            len = strlen(argv[i]);
            printf("Nome troppo lungo: %zu caratteri\n", len);
        } else {
            len = strlen(name_copy);
            printf("Registrato: %s (%zu caratteri)\n", name_copy, len);
            free(name_copy);
        }
    }
    return 0;
}
