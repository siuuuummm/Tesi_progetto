#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Constant tables recovered from .rodata of the stripped binary:
 * 0x00401360: { 0, 1, 2, 3 }  (lane initial values)
 * 0x00401370: { 1, 1, 1, 1 }  (per-lane addends, added after the *3)
 * 0x00401380: { 4, 4, 4, 4 }  (per-lane strides)
 */
static const int lane_base[4] = { 0, 1, 2, 3 };
static const int lane_add[4]  = { 1, 1, 1, 1 };
static const int lane_stride[4] = { 4, 4, 4, 4 };

int main(int argc, char **argv)
{
    uint32_t n;
    uint64_t parsed;
    unsigned long n1;
    int32_t *buf;
    int32_t *p;
    int32_t *end;
    int32_t i0, i1, i2, i3;
    int32_t v0, v1, v2, v3;
    int32_t s0, s1, s2, s3;
    uint32_t sum;
    int32_t rem;
    int32_t rem3;
    uint8_t alloc_bytes;

    if (argc < 2) {
        return 1;
    }

    setvbuf(stdout, (char *)0x0, 2, 0);

    parsed = (uint64_t)strtol(argv[1], 0, 10);
    n = (uint32_t)parsed;

    if (100 < n) {
        puts("Troppi elementi");
        return 1;
    }

    buf = (int32_t *)malloc((unsigned long)((uint32_t)(n * 4 & 0xff)));
    alloc_bytes = (uint8_t)(n * 4);
    printf("Elementi: %u, byte allocati: %u\n", (unsigned int)(parsed & 0xffffffff),
           (unsigned long)alloc_bytes);

    sum = n;
    if (n != 0) {
        uint32_t r32;

        if (n - 1 < 4) {
            r32 = 0;
            sum = 0;
        }
        else {
            i0 = lane_base[0];
            i1 = lane_base[1];
            i2 = lane_base[2];
            i3 = lane_base[3];
            s0 = 0;
            s1 = 0;
            s2 = 0;
            s3 = 0;
            p = buf;
            n1 = (n >> 2 & 0x3fffffff) * 4;
            end = buf + n1;
            do {
                int32_t *next = p + 4;

                v0 = i0 * 3;
                v1 = i1 * 3;
                v2 = i2 * 3;
                v3 = i3 * 3;
                i0 = i0 + lane_stride[0];
                i1 = i1 + lane_stride[1];
                i2 = i2 + lane_stride[2];
                i3 = i3 + lane_stride[3];
                v0 = v0 + lane_add[0];
                v1 = v1 + lane_add[1];
                v2 = v2 + lane_add[2];
                v3 = v3 + lane_add[3];
                *p = v0;
                p[1] = v1;
                p[2] = v2;
                p[3] = v3;
                s0 = s0 + v0;
                s1 = s1 + v1;
                s2 = s2 + v2;
                s3 = s3 + v3;
                p = next;
            } while (end != p);
            sum = (uint32_t)(s0 + s2 + s1 + s3);
            if ((parsed & 3) == 0) {
                goto print_sum;
            }
            r32 = n & 0xfffffffc;
        }

        rem = (int32_t)r32;
        rem3 = rem * 3;
        sum = (uint32_t)(rem3 + 1 + sum);
        if ((((rem + 1 < (int32_t)n) && (sum = (uint32_t)(rem3 + 4 + sum),
             (rem + 2) < (int32_t)n)) &&
            (sum = (uint32_t)(rem3 + 7 + sum), (rem + 3) < (int32_t)n))) {
            sum = (uint32_t)(rem3 + 10 + sum);
        }
    }

print_sum:
    printf("Somma: %u\n", (unsigned long)sum);
    free(buf);
    return 0;
}
