#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Reconstructed from stripped binary via Ghidra decompilation.
 *
 * FUN_004004b6 @ 0x4004b6  -> register_name()
 * FUN_004004f1 @ 0x4004f1  -> main()   (first arg of __libc_start_main in entry @ 0x4003d0)
 *
 * Values transcribed exactly as decompiled:
 *   - strlen < 0x11  (accept names up to 16 chars)
 *   - malloc(0x10)   (16-byte buffer, one byte too small for the 16-char + NUL case)
 *   - strcpy without length check  (intentionally preserved, not "fixed")
 */

char *register_name(char *name)
{
    size_t len;
    char *dest;

    len = strlen(name);
    dest = (char *)0;
    if (len < 0x11) {
        dest = (char *)malloc(0x10);
        strcpy(dest, name);
    }
    return dest;
}

int main(int argc, char **argv)
{
    char *name;
    char *reg;
    size_t len;
    int i;

    setvbuf(stdout, NULL, _IOLBF, 0);
    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            name = argv[i];
            reg = register_name(name);
            if (reg == NULL) {
                len = strlen(name);
                printf("Nome troppo lungo: %zu caratteri\n", len);
            }
            else {
                len = strlen(reg);
                printf("Registrato: %s (%zu caratteri)\n", reg, len);
                free(reg);
            }
        }
    }
    return 0;
}
