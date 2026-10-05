#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  uint8_t bytes_allocated;
  uint32_t i;
  uint32_t n;
  uint32_t sum;
  void *ptr;
  int ret;

  if (argc < 2) {
    ret = 1;
  }
  else {
    setvbuf(stdout, (char *)0x0, 2, 0);
    n = atoi(argv[1]);
    if (n < 0x65) {
      bytes_allocated = (uint8_t)(n << 2);
      ptr = malloc((uint64_t)bytes_allocated);
      printf("Elementi: %u, byte allocati: %u\n", (uint64_t)n, (uint64_t)bytes_allocated);
      sum = 0;
      for (i = 0; i < n; i = i + 1) {
        *(uint32_t *)((long)ptr + (uint64_t)i * 4) = i * 3 + 1;
        sum = sum + *(int32_t *)((long)ptr + (uint64_t)i * 4);
      }
      printf("Somma: %u\n", (uint64_t)sum);
      free(ptr);
      ret = 0;
    }
    else {
      puts("Troppi elementi");
      ret = 1;
    }
  }
  return ret;
}
