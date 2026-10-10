#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv)
{
  uint64_t *end_ptr;
  char *s;
  uint32_t size32;
  size_t len;
  char *ptr;
  uint32_t next_off;
  uint64_t copy_size;
  uint64_t *argp;

  setvbuf(stdout, (char *)0x0, 2, 0);
  if (1 < argc) {
    argp = (uint64_t *)((char *)argv + 8);
    end_ptr = (uint64_t *)((char *)argv + 0x10 + (size_t)(argc - 2) * 8);
    do {
      while (1) {
        s = (char *)*argp;
        len = strlen(s);
        if (0x10 < len) break;
        ptr = (char *)malloc(0x10);
        copy_size = len + 1;
        size32 = (uint32_t)copy_size;
        if (size32 < 8) {
          if ((copy_size & 4) == 0) {
            if ((size32 != 0) && (*ptr = *s, (copy_size & 2) != 0)) {
              *(uint16_t *)(ptr + (size32 - 2)) =
                   *(uint16_t *)(s + (size32 - 2));
            }
          }
          else {
            *(uint32_t *)ptr = *(uint32_t *)s;
            *(uint32_t *)(ptr + (size32 - 4)) =
                 *(uint32_t *)(s + (size32 - 4));
          }
        }
        else {
          *(uint64_t *)(ptr + (size32 - 8)) =
               *(uint64_t *)(s + (size32 - 8));
          if (7 < size32 - 1) {
            copy_size = 0;
            do {
              next_off = (int)copy_size + 8;
              *(uint64_t *)(ptr + copy_size) = *(uint64_t *)(s + copy_size);
              copy_size = next_off;
            } while (next_off < (size32 - 1 & 0xfffffff8));
          }
        }
        printf("Registrato: %s (%zu caratteri)\n", ptr, len);
        argp = argp + 1;
        free(ptr);
        if (argp == end_ptr) {
          return 0;
        }
      }
      argp = argp + 1;
      printf("Nome troppo lungo: %zu caratteri\n", len);
    } while (argp != end_ptr);
  }
  return 0;
}
