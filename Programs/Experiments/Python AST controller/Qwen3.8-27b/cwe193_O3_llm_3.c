#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char **argp;
    char **argend;
    char *name;
    char *buf;
    size_t len;

    setvbuf(stdout, (char *)0, 2, 0);
    if (argc > 1) {
        argp = argv + 1;
        argend = (char **)((char *)argv + 0x10 + (size_t)(argc - 2) * 8);
        do {
            while (1) {
                name = *argp;
                len = strlen(name);
                if (0x10 < len)
                    break;
                buf = (char *)malloc(0x10);
                strcpy(buf, name);
                printf("Registrato: %s (%zu caratteri)\n", buf, len);
                argp = argp + 1;
                free(buf);
                if (argp == argend)
                    return 0;
            }
            argp = argp + 1;
            printf("Nome troppo lungo: %zu caratteri\n", len);
        } while (argp != argend);
    }
    return 0;
}
