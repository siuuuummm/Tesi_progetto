#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Costanti in .rodata lette dal binario */
static const int32_t vec_start[4] = { 0, 1, 2, 3 };   /* 0x00401360 */
static const int32_t vec_add[4]   = { 1, 1, 1, 1 };   /* 0x00401370 */
static const int32_t vec_step[4]  = { 4, 4, 4, 4 };   /* 0x00401380 */

int main(int argc, char **argv)
{
    long parsed;
    uint32_t n;
    uint32_t sum;
    uint32_t start;
    int *arr;
    int step0;
    int step1;
    int step2;
    int step3;
    int add0;
    int add1;
    int add2;
    int add3;
    int idx0;
    int idx1;
    int idx2;
    int idx3;
    int t0;
    int t1;
    int t2;
    int t3;
    int acc0;
    int acc1;
    int acc2;
    int acc3;
    int *p;
    int *p_next;
    int three_base;

    if (argc < 2) {
        return 1;
    }
    setvbuf(stdout, (char *)0x0, 2, 0);
    parsed = strtol(argv[1], 0, 10);
    n = (uint32_t)parsed;
    if (100 < n) {
        puts("Troppi elementi");
        return 1;
    }
    arr = (int *)malloc((uint64_t)(n * 4 & 0xff));
    printf("Elementi: %u, byte allocati: %u\n",
           (uint32_t)(parsed & 0xffffffff),
           (uint8_t)(n * 4));

    step3 = vec_step[3];
    step2 = vec_step[2];
    step1 = vec_step[1];
    step0 = vec_step[0];
    add3 = vec_add[3];
    add2 = vec_add[2];
    add1 = vec_add[1];
    add0 = vec_add[0];

    sum = n;
    if (n != 0) {
        if (n - 1 < 4) {
            start = 0;
            sum = 0;
        } else {
            acc0 = 0;
            acc1 = 0;
            acc2 = 0;
            acc3 = 0;
            p = arr;
            idx0 = vec_start[0];
            idx1 = vec_start[1];
            idx2 = vec_start[2];
            idx3 = vec_start[3];
            do {
                p_next = p + 4;
                t0 = idx0 * 3;
                t1 = idx1 * 3;
                t2 = idx2 * 3;
                t3 = idx3 * 3;
                idx0 = idx0 + step0;
                idx1 = idx1 + step1;
                idx2 = idx2 + step2;
                idx3 = idx3 + step3;
                t0 = t0 + add0;
                t1 = t1 + add1;
                t2 = t2 + add2;
                t3 = t3 + add3;
                p[0] = t0;
                p[1] = t1;
                p[2] = t2;
                p[3] = t3;
                acc0 = acc0 + t0;
                acc1 = acc1 + t1;
                acc2 = acc2 + t2;
                acc3 = acc3 + t3;
                p = p_next;
            } while (arr + (n >> 2) * 4 != p_next);
            sum = (uint32_t)(acc0 + acc2 + acc1 + acc3);
            if ((n & 3) == 0) {
                goto print_sum;
            }
            start = n & 0xfffffffc;
        }
        three_base = start * 3;
        sum = three_base + 1 + sum;
        if (((start + 1 < n) && (sum = three_base + 4 + sum, start + 2 < n)) &&
            (sum = three_base + 7 + sum, start + 3 < n)) {
            sum = three_base + 10 + sum;
        }
    }

print_sum:
    printf("Somma: %u\n", sum);
    free(arr);
    return 0;
}