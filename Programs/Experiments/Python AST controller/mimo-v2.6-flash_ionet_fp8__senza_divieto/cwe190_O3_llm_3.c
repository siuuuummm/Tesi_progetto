#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* Dati in .rodata a 0x00401360 (seed iniziali dei 4 lane) */
static const int32_t seed_init[4] = {0, 1, 2, 3};
/* Dati in .rodata a 0x00401370 (addendi dei 4 lane) */
static const int32_t addend_tbl[4] = {1, 1, 1, 1};
/* Dati in .rodata a 0x00401380 (incrementi dei 4 lane) */
static const int32_t step_tbl[4] = {4, 4, 4, 4};

int main(int param_1, char **param_2)
{
  int32_t prod0;
  int32_t prod1;
  int32_t prod2;
  int32_t prod3;
  int32_t add0;
  int32_t add1;
  int32_t add2;
  int32_t add3;
  int32_t step0;
  int32_t step1;
  int32_t step2;
  int32_t step3;
  uint32_t acc_total;
  int32_t *ptr;
  int32_t *p;
  int32_t *p_next;
  unsigned long parsed;
  uint32_t n;
  uint32_t vec_index;
  int32_t triple;
  int32_t lane0;
  int32_t lane1;
  int32_t lane2;
  int32_t lane3;
  int32_t acc0;
  int32_t acc1;
  int32_t acc2;
  int32_t acc3;

  if (param_1 < 2) {
    return 1;
  }
  setvbuf(stdout, (char *)0x0, 2, 0);
  parsed = (unsigned long)strtol(param_2[1], (char **)0x0, 10);
  n = (uint32_t)parsed;
  if (100 < n) {
    puts("Troppi elementi");
    return 1;
  }
  ptr = (int32_t *)malloc((unsigned long)(n * 4 & 0xff));
  printf("Elementi: %u, byte allocati: %u\n",
         parsed & 0xffffffff,
         (unsigned long)(uint8_t)(n * 4));
  step3 = step_tbl[3];
  step2 = step_tbl[2];
  step1 = step_tbl[1];
  step0 = step_tbl[0];
  add3 = addend_tbl[3];
  add2 = addend_tbl[2];
  add1 = addend_tbl[1];
  add0 = addend_tbl[0];
  acc_total = n;
  if (n != 0) {
    if (n - 1 < 4) {
      vec_index = 0;
      acc_total = 0;
    }
    else {
      acc0 = 0;
      acc1 = 0;
      acc2 = 0;
      acc3 = 0;
      p = ptr;
      lane0 = seed_init[0];
      lane1 = seed_init[1];
      lane2 = seed_init[2];
      lane3 = seed_init[3];
      do {
        p_next = p + 4;
        prod0 = lane0 * 3;
        prod1 = lane1 * 3;
        prod2 = lane2 * 3;
        prod3 = lane3 * 3;
        lane0 = lane0 + step0;
        lane1 = lane1 + step1;
        lane2 = lane2 + step2;
        lane3 = lane3 + step3;
        prod0 = prod0 + add0;
        prod1 = prod1 + add1;
        prod2 = prod2 + add2;
        prod3 = prod3 + add3;
        *p = prod0;
        p[1] = prod1;
        p[2] = prod2;
        p[3] = prod3;
        acc0 = acc0 + prod0;
        acc1 = acc1 + prod1;
        acc2 = acc2 + prod2;
        acc3 = acc3 + prod3;
        p = p_next;
      } while (ptr + (parsed >> 2 & 0x3fffffff) * 4 != p_next);
      acc_total = acc0 + acc2 + acc1 + acc3;
      if ((parsed & 3) == 0) goto print_sum;
      vec_index = n & 0xfffffffc;
    }
    triple = vec_index * 3;
    acc_total = triple + 1 + acc_total;
    if (((vec_index + 1 < n) && (acc_total = triple + 4 + acc_total, vec_index + 2 < n)) &&
        (acc_total = triple + 7 + acc_total, vec_index + 3 < n)) {
      acc_total = triple + 10 + acc_total;
    }
  }
print_sum:
  printf("Somma: %u\n", acc_total);
  free(ptr);
  return 0;
}