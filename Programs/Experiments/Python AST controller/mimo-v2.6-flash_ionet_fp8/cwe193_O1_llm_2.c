#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *register_name(char *name)
{
    size_t len;
    char *copy;

    len = strlen(name);
    copy = NULL;
    if (len < 0x11) {
        copy = malloc(0x10);
        strcpy(copy, name);
    }
    return copy;
}

int main(int argc, char **argv)
{
    char *name;
    char *copy;
    size_t len;
    char **cursor;

    setvbuf(stdout, NULL, 2, 0);
    if (1 < argc) {
        cursor = (char **)((char *)argv + 8);
        do {
            name = *cursor;
            copy = register_name(name);
            if (copy == NULL) {
                len = strlen(name);
                printf("Nome troppo lungo: %zu caratteri\n", len);
            } else {
                len = strlen(copy);
                printf("Registrato: %s (%zu caratteri)\n", copy, len);
                free(copy);
            }
            cursor = cursor + 1;
        } while (cursor != (char **)((char *)argv + 0x10 + (size_t)(argc - 2) * 8));
    }
    return 0;
}
