#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Original symbol: FUN_004004b6 */
char *register_name(char *name)
{
    size_t len;
    char *dest;

    len = strlen(name);
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, name);
    }
    else {
        dest = (char *)0x0;
    }
    return dest;
}

/* Original symbol: FUN_00400507 (main, first argument of __libc_start_main) */
int main(int argc, char **argv)
{
    char *s;
    size_t len;
    int i;

    setvbuf(stdout, (char *)0x0, 2, 0);
    for (i = 1; i < argc; i = i + 1) {
        s = register_name(*(char **)(argv + i));
        if (s == (char *)0x0) {
            len = strlen(*(char **)(argv + i));
            printf("Nome troppo lungo: %zu caratteri\n", len);
        }
        else {
            len = strlen(s);
            printf("Registrato: %s (%zu caratteri)\n", s, len);
            free(s);
        }
    }
    return 0;
}
