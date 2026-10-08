/*
 * test_O3 - reconstructed C source from the stripped binary (test_O3).
 *
 * What the program does:
 *   1. Reads an element count n from argv[1] (strtol, base 10).
 *   2. If n > 100, prints "Troppi elementi" and returns 1.
 *   3. Allocates a buffer using only the low 8 bits of the requested byte
 *      count:  malloc((n * 4) & 0xff).  For n where n*4 >= 256 this is a
 *      deliberate heap overflow: the buffer is far too small for the n
 *      4-byte elements that are then written into it.
 *   4. Prints the number of elements and the (truncated) allocated byte count.
 *   5. Fills buf[i] with the arithmetic sequence  3*i + 1  and accumulates the
 *      running sum.
 *   6. Prints the sum and frees the buffer.
 *
 * The sum is therefore  sum(i=0..n-1) (3*i + 1)  ==  n*(3*n - 1) / 2.
 *
 * Strings recovered from the .rodata section (file offset 0x1300, VMA 0x401300):
 *   0x401310  "Troppi elementi"
 *   0x401320  "Somma: %u\n"
 *   0x401330  "Elementi: %u, byte allocati: %u\n"
 *
 * The three 16-byte constant blocks in .rodata used by the -O3 vectorised body
 * of main() (loaded with MOVDQA in the binary) are:
 *   0x401360  {0, 1, 2, 3}   initial vector state  (== i mod 4 / lane seeds)
 *   0x401370  {1, 1, 1, 1}   per-element constant  (== the "+1" of 3*i+1)
 *   0x401380  {4, 4, 4, 4}   per-group increment   (== 4, so 3*(4*g+lane)+1)
 * These are the compiler's vectorisation of  buf[i] = 3*i + 1;  the value
 * written at index (4*g + lane) is  3*(4*g + lane) + 1  ==  3*i + 1.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    /* if (argc < 2) return 1; */
    if (argc < 2) {
        return 1;
    }

    /* setvbuf(stdout, NULL, _IONBF, 0);   (mode 2 == _IONBF, unbuffered) */
    setvbuf(stdout, (char *)0x0, 2, 0);

    /* n = strtol(argv[1], NULL, 10); */
    unsigned int n = (unsigned int)strtol(argv[1], NULL, 10);

    /* if (n > 100) { puts("Troppi elementi"); return 1; } */
    if (n > 100) {
        puts("Troppi elementi");
        return 1;
    }

    /*
     * Buffer overflow: only the low 8 bits of (n * 4) bytes are allocated,
     * but n four-byte elements are written below.
     */
    size_t allocated = (size_t)(n * 4) & 0xff;
    int *__ptr = (int *)malloc(allocated);

    /* printf("Elementi: %u, byte allocati: %u\n", n, (unsigned char)(n * 4)); */
    printf("Elementi: %u, byte allocati: %u\n",
           n, (unsigned int)(unsigned char)(n * 4));

    unsigned int sum = 0;
    for (unsigned int i = 0; i < n; i++) {
        __ptr[i] = 3 * (int)i + 1;   /* buf[i] = 3*i + 1 */
        sum += (unsigned int)__ptr[i];
    }

    /* printf("Somma: %u\n", sum); */
    printf("Somma: %u\n", sum);

    free(__ptr);
    return 0;
}
