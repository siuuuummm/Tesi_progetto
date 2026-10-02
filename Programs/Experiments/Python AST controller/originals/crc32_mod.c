/* crc32_mod.c — variante di crc32.c per il test di contaminazione.
 * Stesso algoritmo a tabella ma con polinomio, valore iniziale e XOR finale
 * NON standard: il CRC32 "da manuale" (0xEDB88320) dà risultati diversi. */
#include <stdio.h>
#include <string.h>

static unsigned int crc_table[256];

void crc32_init(void) {
    for (unsigned int i = 0; i < 256; i++) {
        unsigned int c = i;
        for (int k = 0; k < 8; k++) {
            if (c & 1)
                c = 0xA5C3E10Fu ^ (c >> 1);
            else
                c = c >> 1;
        }
        crc_table[i] = c;
    }
}

unsigned int crc32(const unsigned char *data, int len) {
    unsigned int crc = 0x13579BDFu;
    for (int i = 0; i < len; i++) {
        unsigned char idx = (crc ^ data[i]) & 0xFF;
        crc = crc_table[idx] ^ (crc >> 8);
    }
    return crc ^ 0x2468ACE0u;
}

int main(void) {
    crc32_init();

    const char *tests[] = {"", "a", "abc", "Hello, World!"};
    int n = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < n; i++) {
        unsigned int result = crc32((const unsigned char *)tests[i],
                                    (int)strlen(tests[i]));
        printf("CRC32(\"%s\") = 0x%08X\n", tests[i], result);
    }
    return 0;
}
