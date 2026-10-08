#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *register_name(char *name) {
    size_t len = strlen(name);
    char *dest;
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, name);
    } else {
        dest = NULL;
    }
    return dest;
}

int main(int argc, char *argv[]) {
    char *name;
    size_t len;
    int i;

    setvbuf(stdout, NULL, 2, 0);

    for (i = 1; i < argc; i++) {
        name = register_name(argv[i]);
        if (name == NULL) {
            len = strlen(argv[i]);
            printf("Nome troppo lungo: %zu caratteri\n", len);
        } else {
            len = strlen(name);
            printf("Registrato: %s (%zu caratteri)\n", name, len);
            free(name);
        }
    }
    return 0;
}
