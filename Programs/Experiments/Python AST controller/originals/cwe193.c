/* cwe193.c — CWE-193: Off-by-one Error.
 * Il controllo di lunghezza usa > invece di >=: un nome di esattamente 16
 * caratteri passa e strcpy scrive il terminatore oltre il buffer di 16 byte. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 16

char *copy_name(const char *src) {
    size_t len = strlen(src);
    if (len > MAX_NAME)          /* vulnerabile: dovrebbe essere >= */
        return NULL;
    char *dst = malloc(MAX_NAME);
    strcpy(dst, src);
    return dst;
}

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);
    for (int i = 1; i < argc; i++) {
        char *name = copy_name(argv[i]);
        if (name == NULL) {
            printf("Nome troppo lungo: %zu caratteri\n", strlen(argv[i]));
            continue;
        }
        printf("Registrato: %s (%zu caratteri)\n", name, strlen(name));
        free(name);
    }
    return 0;
}
