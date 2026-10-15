#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    size_t sVar3;
    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        char **puVar6 = (char **)(argv + 1);
        char **puVar1 = (char **)(argv + 2 + (argc - 2));
        do {
            while( 1 ) {
                char *__s = *puVar6;
                sVar3 = strlen(__s);
                if (0x10 < sVar3) break;
                char *__ptr = (char *)malloc(0x10);
                strcpy(__ptr, __s);
                printf("Registrato: %s (%zu caratteri)\n", __ptr, sVar3);
                puVar6 = puVar6 + 1;
                free(__ptr);
                if (puVar6 == puVar1) {
                    return 0;
                }
            }
            puVar6 = puVar6 + 1;
            printf("Nome troppo lungo: %zu caratteri\n", sVar3);
        } while (puVar6 != puVar1);
    }
    return 0;
}
