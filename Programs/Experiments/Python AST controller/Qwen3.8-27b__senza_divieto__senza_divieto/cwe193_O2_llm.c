#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *copia_nome(char *nome)
{
    char *buf = 0;
    size_t n = strlen(nome);
    if (n < 0x11) {
        buf = malloc(0x10);
        memcpy(buf, nome, n + 1);
    }
    return buf;
}

int main(int argc, char **argv)
{
    setvbuf(stdout, 0, 2, 0);
    if (argc > 1) {
        int i;
        for (i = 1; i < argc; i++) {
            size_t n = strlen(argv[i]);
            if (n > 0x10) {
                printf("Nome troppo lungo: %zu caratteri\n", n);
                continue;
            }
            char *buf = malloc(0x10);
            memcpy(buf, argv[i], n + 1);
            printf("Registrato: %s (%zu caratteri)\n", buf, n);
            free(buf);
        }
    }
    return 0;
}
