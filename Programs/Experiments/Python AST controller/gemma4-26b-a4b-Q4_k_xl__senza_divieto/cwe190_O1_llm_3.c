#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        setvbuf(stdout, NULL, 2, 0);
        uint32_t uVar1 = (uint32_t)strtol(argv[1], NULL, 10);
        
        if (uVar1 < 101) {
            uint32_t alloc_size = (uVar1 * 4) & 0xFF;
            int32_t *ptr = (int32_t *)malloc(alloc_size);
            
            printf("Elementi: %u, byte allocati: %u\n", uVar1, alloc_size);
            
            if (uVar1 != 0) {
                int32_t limit = (int32_t)uVar1 * 3;
                int32_t current_val = 1;
                uVar1 = 0;
                int32_t *p = ptr;
                
                do {
                    *p = current_val;
                    uVar1 += (uint32_t)current_val;
                    current_val += 3;
                    p++;
                } while (current_val != limit + 1);
            }
            
            printf("Somma: %u\n", uVar1);
            free(ptr);
            return 0;
        } else {
            puts("Troppi elementi");
            return 1;
        }
    }
    return 1;
}
