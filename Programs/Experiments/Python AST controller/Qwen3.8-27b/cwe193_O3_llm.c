#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *alloca_nome(char *s)
{
    size_t len = strlen(s);
    char *buf = NULL;
    if (len < 0x11) {
        buf = malloc(0x10);
        memcpy(buf, s, len + 1);
    }
    return buf;
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, 2, 0);
    if (argc > 1) {
        char **arg = argv + 1;
        char **end = argv + argc;
        while (arg != end) {
            size_t len = strlen(*arg);
            if (len > 0x10) {
                arg++;
                printf("Nome troppo lungo: %zu caratteri\n", len);
                continue;
            }
            char *buf = malloc(0x10);
            memcpy(buf, *arg, len + 1);
            printf("Registrato: %s (%zu caratteri)\n", buf, len);
            arg++;
            free(buf);
        }
    }
    return 0;
}
