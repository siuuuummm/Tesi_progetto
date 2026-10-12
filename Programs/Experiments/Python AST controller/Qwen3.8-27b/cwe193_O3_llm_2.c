#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        char **arg = (char **)(argv + 1);
        char **end = (char **)(argv + argc);
        do {
            char *s = *arg;
            size_t len = strlen(s);
            if (0x10 < len) {
                arg = arg + 1;
                printf("Nome troppo lungo: %zu caratteri\n", len);
            }
            else {
                char *buf = (char *)malloc(0x10);
                strcpy(buf, s);
                printf("Registrato: %s (%zu caratteri)\n", buf, len);
                arg = arg + 1;
                free(buf);
                if (arg == end) {
                    return 0;
                }
            }
        } while (arg != end);
    }
    return 0;
}
