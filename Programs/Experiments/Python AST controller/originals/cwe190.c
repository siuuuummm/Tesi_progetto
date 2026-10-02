/* cwe190.c — CWE-190: Integer Overflow → CWE-122: Heap-based Buffer Overflow.
 * La dimensione dell'allocazione viene troncata a 8 bit: con count >= 64 il
 * buffer è più piccolo del necessario e il ciclo scrive oltre la fine. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    setvbuf(stdout, NULL, _IONBF, 0);

    unsigned int count = (unsigned int)atoi(argv[1]);
    if (count > 100) {
        printf("Troppi elementi\n");
        return 1;
    }

    uint8_t bytes = count * sizeof(uint32_t);   /* vulnerabile: wrap a 8 bit */
    uint32_t *values = malloc(bytes);
    printf("Elementi: %u, byte allocati: %u\n", count, bytes);

    uint32_t sum = 0;
    for (unsigned int i = 0; i < count; i++) {
        values[i] = i * 3 + 1;
        sum += values[i];
    }
    printf("Somma: %u\n", sum);

    free(values);
    return 0;
}
