#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    setvbuf(stdout, (char *)0, 2, 0);

    if (argc > 1) {
        char **argv_end = &argv[argc - 1];

        while (1) {
            char *s = *argv;
            size_t len = strlen(s);

            if (len > 0x10) {
                argv++;
                printf("Nome troppo lungo: %zu caratteri\n", len);
                if (argv == argv_end) {
                    return 0;
                }
                continue;
            }

            char *dst = (char *)malloc(0x10);
            size_t copy_len = len + 1;

            if (copy_len < 8) {
                if ((copy_len & 4) == 0) {
                    if (copy_len != 0) {
                        *dst = *s;
                        if ((copy_len & 2) != 0) {
                            *(unsigned short *)(dst + (copy_len - 2)) =
                                *(unsigned short *)(s + (copy_len - 2));
                        }
                    }
                } else {
                    *(unsigned int *)dst = *(unsigned int *)s;
                    *(unsigned int *)(dst + (copy_len - 4)) =
                        *(unsigned int *)(s + (copy_len - 4));
                }
            } else {
                *(unsigned long long *)(dst + (copy_len - 8)) =
                    *(unsigned long long *)(s + (copy_len - 8));
                if (copy_len - 1 > 7) {
                    unsigned long long i = 0;
                    do {
                        unsigned long long next = i + 8;
                        *(unsigned long long *)(dst + i) = *(unsigned long long *)(s + i);
                        i = next;
                    } while (next < ((copy_len - 1) & 0xfffffff8));
                }
            }

            printf("Registrato: %s (%zu caratteri)\n", dst, len);
            argv++;
            free(dst);

            if (argv == argv_end) {
                return 0;
            }
        }
    }

    return 0;
}
