#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char *registra_nome(char *nome)
{
    size_t len;
    char *dest;

    len = strlen(nome);
    dest = (char *)0x0;
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, nome);
    }
    return dest;
}

int main(int argc, long argv)
{
    char *nome;
    char *registrato;
    size_t len;
    uint64_t *p;

    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        p = (uint64_t *)(argv + 8);
        do {
            nome = (char *)*p;
            registrato = registra_nome(nome);
            if (registrato == (char *)0x0) {
                len = strlen(nome);
                printf("Nome troppo lungo: %zu caratteri\n", len);
            }
            else {
                len = strlen(registrato);
                printf("Registrato: %s (%zu caratteri)\n", registrato, len);
                free(registrato);
            }
            p = p + 1;
        } while (p != (uint64_t *)(argv + 0x10 + (unsigned long)(argc - 2) * 8));
    }
    return 0;
}