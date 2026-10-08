#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *process_name(char *param_1) {
    size_t sVar1;
    char *__dest;

    sVar1 = strlen(param_1);
    if (sVar1 < 0x11) {
        __dest = (char *)malloc(0x10);
        strcpy(__dest, param_1);
    } else {
        __dest = (char *)0;
    }
    return __dest;
}

int main(int argc, char **argv) {
    char *__s;
    size_t sVar1;
    int local_c;

    setvbuf(stdout, (char *)0, 2, 0);
    for (local_c = 1; local_c < argc; local_c = local_c + 1) {
        __s = process_name(argv[local_c]);
        if (__s == (char *)0) {
            sVar1 = strlen(argv[local_c]);
            printf("Nome troppo lungo: %zu caratteri\n", sVar1);
        } else {
            sVar1 = strlen(__s);
            printf("Registrato: %s (%zu caratteri)\n", __s, sVar1);
            free(__s);
        }
    }
    return 0;
}
