#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *registra_nome(char *nome)
{
    size_t len;
    char *dest;

    len = strlen(nome);
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, nome);
    }
    else {
        dest = (char *)0;
    }
    return dest;
}

int main(int argc, char **argv)
{
    char *s;
    size_t len;
    int i;

    setvbuf(stdout, (char *)0, 2, 0);
    for (i = 1; i < argc; i = i + 1) {
        s = registra_nome(argv[i]);
        if (s == (char *)0) {
            len = strlen(argv[i]);
            printf("Nome troppo lungo: %zu caratteri\n", len);
        }
        else {
            len = strlen(s);
            printf("Registrato: %s (%zu caratteri)\n", s, len);
            free(s);
        }
    }
    return 0;
}
