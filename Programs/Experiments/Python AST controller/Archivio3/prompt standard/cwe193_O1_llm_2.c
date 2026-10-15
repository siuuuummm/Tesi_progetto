#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *register_name(const char *input)
{
    size_t len;
    char *dest;

    len = strlen(input);
    dest = NULL;
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, input);
    }
    return dest;
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        char **ptr = &argv[1];
        do {
            char *result = register_name(*ptr);
            if (result == NULL) {
                size_t len = strlen(*ptr);
                printf("Nome troppo lungo: %zu caratteri\n", len);
            }
            else {
                size_t len = strlen(result);
                printf("Registrato: %s (%zu caratteri)\n", result, len);
                free(result);
            }
            ptr = ptr + 1;
        } while (ptr != &argv[2 + (argc - 2)]);
    }
    return 0;
}
