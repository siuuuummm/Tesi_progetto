#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *register_name(char *param_1) {
    size_t sVar1;
    char *__dest;

    sVar1 = strlen(param_1);
    __dest = (char *)0x0;
    if (sVar1 < 0x11) {
        __dest = (char *)malloc(0x10);
        strcpy(__dest, param_1);
    }
    return __dest;
}

int main(int argc, char *argv[]) {
    char *__s;
    char *__s_00;
    size_t sVar1;
    char **puVar2;

    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        puVar2 = (char **)((char *)argv + 8);
        do {
            __s = *puVar2;
            __s_00 = register_name(__s);
            if (__s_00 == (char *)0x0) {
                sVar1 = strlen(__s);
                printf("Nome troppo lungo: %zu caratteri\n", sVar1);
            } else {
                sVar1 = strlen(__s_00);
                printf("Registrato: %s (%zu caratteri)\n", __s_00, sVar1);
                free(__s_00);
            }
            puVar2++;
        } while ((char *)puVar2 != (char *)((char *)argv + 0x10 + (uintptr_t)(argc - 2) * 8));
    }
    return 0;
}
