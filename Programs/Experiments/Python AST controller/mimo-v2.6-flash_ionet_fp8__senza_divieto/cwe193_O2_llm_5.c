#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char **end_ptr;
    char *s;
    uint32_t copy_len32;
    size_t len;
    char *ptr;
    uint32_t offset;
    uint64_t copy_len;
    char **cur_ptr;

    setvbuf(stdout, (char *)0x0, 2, 0);
    if (1 < argc) {
        cur_ptr = argv + 1;
        end_ptr = argv + 2 + (size_t)(argc - 2);
        do {
            while (1) {
                s = *cur_ptr;
                len = strlen(s);
                if (0x10 < len) break;
                ptr = (char *)malloc(0x10);
                copy_len = len + 1;
                copy_len32 = (uint32_t)copy_len;
                if (copy_len32 < 8) {
                    if ((copy_len & 4) == 0) {
                        if ((copy_len32 != 0) &&
                            (*ptr = *s, (copy_len & 2) != 0)) {
                            *(uint16_t *)(ptr + (copy_len & 0xffffffff) - 2) =
                                *(uint16_t *)(s + (copy_len & 0xffffffff) - 2);
                        }
                    } else {
                        *(uint32_t *)ptr = *(uint32_t *)s;
                        *(uint32_t *)(ptr + (copy_len & 0xffffffff) - 4) =
                            *(uint32_t *)(s + (copy_len & 0xffffffff) - 4);
                    }
                } else {
                    *(uint64_t *)(ptr + (copy_len & 0xffffffff) - 8) =
                        *(uint64_t *)(s + (copy_len & 0xffffffff) - 8);
                    if (7 < copy_len32 - 1) {
                        copy_len = 0;
                        do {
                            offset = (int32_t)copy_len + 8;
                            *(uint64_t *)(ptr + copy_len) =
                                *(uint64_t *)(s + copy_len);
                            copy_len = (uint64_t)offset;
                        } while (offset < ((copy_len32 - 1) & 0xfffffff8));
                    }
                }
                printf("Registrato: %s (%zu caratteri)\n", ptr, len);
                cur_ptr = cur_ptr + 1;
                free(ptr);
                if (cur_ptr == end_ptr) {
                    return 0;
                }
            }
            cur_ptr = cur_ptr + 1;
            printf("Nome troppo lungo: %zu caratteri\n", len);
        } while (cur_ptr != end_ptr);
    }
    return 0;
}