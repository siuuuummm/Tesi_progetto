#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *s;
    size_t len;
    char *ptr;
    char **cur;
    char **end;

    setvbuf(stdout, (char *)0x0, _IONBF, 0);
    if (1 < argc) {
        cur = argv + 1;
        end = argv + argc;
        do {
            while (1) {
                s = *cur;
                len = strlen(s);
                if (0x10 < len)
                    break;
                ptr = (char *)malloc(0x10);
                memcpy(ptr, s, len + 1);
                printf("Registrato: %s (%zu caratteri)\n", ptr, len);
                cur = cur + 1;
                free(ptr);
                if (cur == end) {
                    return 0;
                }
            }
            cur = cur + 1;
            printf("Nome troppo lungo: %zu caratteri\n", len);
        } while (cur != end);
    }
    return 0;
}
