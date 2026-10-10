#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *buf;
    char *endptr;
    int cmp;

    if (argc <= 2) {
        return 1;
    }

    setvbuf(stdout, NULL, _IONBF, 0);

    buf = (char *)malloc(0x20);

    {
        int i;
        for (i = 8; i != 0; i--) {
            *(unsigned int *)(buf + (i - 1) * 4) = 0;
        }
    }

    strncpy(buf, argv[1], 0x17);
    *(unsigned int *)(buf + 0x1c) = 1000;

    printf("Token: %s\n", buf);

    cmp = strcmp(argv[2], "admin");

    if (cmp == 0) {
        free(buf);
        puts("Access denied\n");
    }

    if (argc > 3) {
        endptr = (char *)strtol(argv[3], NULL, 10);
    }

    if (*(unsigned int *)(buf + 0x18) == 0) {
        printf("Token accepted\n", buf);
    } else {
        printf("No token provided\n", buf);
    }

    if (cmp == 0) {
        free(buf);
        return 0;
    }

    return 0;
}
