#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    setvbuf(stdout, (char *)0, 2, 0);
    if (1 < argc) {
        char **arg;
        for (arg = &argv[1]; arg <= &argv[argc - 1]; arg++) {
            char *s = *arg;
            size_t len = strlen(s);
            if (0x10 < len) {
                printf("Nome troppo lungo: %zu caratteri\n", len);
            }
            else {
                char *ptr = malloc(0x10);
                strcpy(ptr, s);
                printf("Registrato: %s (%zu caratteri)\n", ptr, len);
                free(ptr);
            }
        }
    }
    return 0;
}
