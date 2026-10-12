#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    setvbuf(stdout, (char *)0x0, 2, 0);

    if (1 < argc) {
        char **end = argv + 2 + (size_t)(argc - 2); /* argv + argc */
        char **p = argv + 1;                        /* argv + 8 */

        for (;;) {
            char *s = *p;
            size_t len = strlen(s);

            if (0x10 < len) {
                /* stringhe troppo lunghe: salto la copia */
                printf("Nome troppo lungo: %zu caratteri\n", len);
            } else {
                char *buf = (char *)malloc(0x10);
                /* copia di strlen+1 byte = strcpy */
                strcpy(buf, s);
                printf("Registrato: %s (%zu caratteri)\n", buf, len);
                free(buf);
            }

            p = p + 1;
            if (p == end) {
                return 0;
            }
        }
    }
    return 0;
}
