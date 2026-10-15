#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    setvbuf(stdout, NULL, _IOLBF, 0);

    if (1 < argc) {
        char **puVar6 = argv + 1;
        char **puVar1 = argv + argc;
        size_t sVar3;

        do {
            while (1) {
                char *__s = *puVar6;
                sVar3 = strlen(__s);

                if (0x10 < sVar3) {
                    break;
                }

                char *__ptr = (char *)malloc(0x10);
                size_t uVar5 = sVar3 + 1;

                memcpy(__ptr, __s, uVar5);

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
