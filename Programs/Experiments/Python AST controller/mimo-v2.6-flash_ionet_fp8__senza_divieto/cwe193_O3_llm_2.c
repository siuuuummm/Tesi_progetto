#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * Espansione inline di memcpy(dst, src, n) generata dal compilatore per
 * n = len + 1 (osservata in FUN_004003c0 @ 0x400460 e in FUN_004005e0
 * @ 0x400606).  Struttura di controllo identica al binario:
 *
 *   if (n < 8) {
 *       if (n & 4)      -> 2 scritture da 4 byte (offset 0 e n-4)
 *       else if (n != 0)-> 1 byte a offset 0, poi se (n & 2) 2 byte a n-2
 *   } else {
 *       8 byte a offset n-8
 *       m = (n - 1) & ~7
 *       do { 8 byte a offset off; off += 8; } while (off < m);
 *   }
 */
static void copy_inline(char *dst, const char *src, unsigned int n)
{
    unsigned int off;
    unsigned int m;

    if (n < 8) {
        if (n & 4U) {
            *(uint32_t *)(dst + 0) = *(const uint32_t *)(src + 0);
            *(uint32_t *)(dst + n - 4) = *(const uint32_t *)(src + n - 4);
        } else if (n != 0) {
            dst[0] = src[0];
            if (n & 2U) {
                *(uint16_t *)(dst + n - 2) = *(const uint16_t *)(src + n - 2);
            }
        }
    } else {
        *(uint64_t *)(dst + n - 8) = *(const uint64_t *)(src + n - 8);
        m = (n - 1U) & ~7U;
        off = 0;
        do {
            *(uint64_t *)(dst + off) = *(const uint64_t *)(src + off);
            off += 8;
        } while (off < m);
    }
}

/*
 * main (FUN_004003c0):
 *   setvbuf(stdout, NULL, _IONBF, 0);
 *   for (i = 1; i < argc; i++) {
 *       len = strlen(argv[i]);
 *       if (len > 16)
 *           printf("Nome troppo lungo: %zu caratteri\n", len);
 *       else {
 *           copy = malloc(16);
 *           memcpy(copy, argv[i], len + 1);            // inline
 *           printf("Registrato: %s (%zu caratteri)\n", copy, len);
 *           free(copy);
 *       }
 *   }
 *   return 0;
 */
int main(int argc, char **argv)
{
    int i;
    size_t len;
    char *copy;
    const char *src;

    setvbuf(stdout, NULL, _IONBF, 0);

    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            src = argv[i];
            len = strlen(src);
            if (len > 16) {
                printf("Nome troppo lungo: %zu caratteri\n", len);
            } else {
                copy = (char *)malloc(16);
                copy_inline(copy, src, (unsigned int)(len + 1));
                printf("Registrato: %s (%zu caratteri)\n", copy, len);
                free(copy);
            }
        }
    }
    return 0;
}

/*
 * FUN_004005e0 - helper non raggiunta dal main nel binario (nessuna call
 * in .text), stessa logica della copia inline di main:
 *   len = strlen(s);
 *   if (len > 16) return NULL;
 *   copy = malloc(16);
 *   memcpy(copy, s, len + 1);   // inline
 *   return copy;
 */
char *duplicate_short_name(const char *s)
{
    size_t len;
    char *copy;

    len = strlen(s);
    if (len > 16) {
        copy = NULL;
        return copy;
    }
    copy = (char *)malloc(16);
    copy_inline(copy, s, (unsigned int)(len + 1));
    return copy;
}
