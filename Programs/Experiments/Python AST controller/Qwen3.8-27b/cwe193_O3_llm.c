#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *registrati(char *nome)
{
    size_t len = strlen(nome);
    char *buf = (char *)0x0;
    if (len < 0x11) {
        buf = (char *)malloc(0x10);
        memcpy(buf, nome, len + 1);
    }
    return buf;
}

int main(int argc, char **argv)
{
    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        int i;
        for (i = 1; i < argc; i++) {
            size_t len = strlen(argv[i]);
            char *buf = registrati(argv[i]);
            if (buf != NULL) {
                printf("Registrato: %s (%zu caratteri)\n", buf, len);
                free(buf);
            }
            else {
                printf("Nome troppo lungo: %zu caratteri\n", len);
            }
        }
    }
    return 0;
}
