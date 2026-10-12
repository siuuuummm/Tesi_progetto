#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Helper: allocates a 16-byte buffer and copies the given name
 * (including the terminating NUL) into it. Returns NULL if the name
 * is too long to fit.
 */
static char *copia_nome(const char *nome)
{
    size_t len = strlen(nome);
    char *copia = (char *)0;

    if (len < 0x11) {
        copia = (char *)malloc(0x10);
        memcpy(copia, nome, len + 1);
    }

    return copia;
}

int main(int argc, char **argv)
{
    setvbuf(stdout, (char *)0, 2, 0);

    if (1 < argc) {
        char **iter = &argv[1];
        char **fine = &argv[argc];

        while (iter != fine) {
            char *nome = *iter;
            size_t len = strlen(nome);

            if (0x10 < len) {
                iter = iter + 1;
                printf("Nome troppo lungo: %zu caratteri\n", len);
                continue;
            }

            char *copia = (char *)malloc(0x10);
            memcpy(copia, nome, len + 1);
            printf("Registrato: %s (%zu caratteri)\n", copia, len);
            iter = iter + 1;
            free(copia);
        }
    }

    return 0;
}
