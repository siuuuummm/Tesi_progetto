#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Copia il nome nel buffer allocato: ammette stringhe di lunghezza < 0x11. */
static char *registra_nome(char *nome)
{
    size_t len;
    char *dest;

    len = strlen(nome);
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, nome);
    }
    else {
        dest = (char *)0x0;
    }
    return dest;
}

int main(int argc, char **argv)
{
    char *nome;
    size_t len;
    int i;

    setvbuf(stdout, (char *)0x0, 2, 0);
    for (i = 1; i < argc; i = i + 1) {
        nome = registra_nome(argv[i]);
        if (nome == (char *)0x0) {
            len = strlen(argv[i]);
            printf("Nome troppo lungo: %zu caratteri\n", len);
        }
        else {
            len = strlen(nome);
            printf("Registrato: %s (%zu caratteri)\n", nome, len);
            free(nome);
        }
    }
    return 0;
}
