#include <stdio.h>
#include <stdint.h>

// Funzione di stampa dati originali e cifrati
typedef uint32_t u32;

// Funzione: stampa_esempio
void stampa_esempio(void) {
    printf("Originale: %08X %08X\n", 0xdeadbeef, 0xcafebabe);
    printf("Cifrato:   %08X %08X\n", 0x9dee733b, 0xc7802f9d);
}

// Funzione: cifra_round
// Esegue un singolo round di cifratura basato su una key
u32 cifra_round(u32 dato, int key) {
    return ((dato << 5) | (dato >> 27)) ^ (key + 0x9e3779b9U);
}

// Funzione: cifra_blocco
// Applica 8 round di "cifratura" su due parole da 32 bit
void cifra_blocco(u32 *a, u32 *b, int key) {
    u32 tmp_a = *a, tmp_b;
    *a = (key + 0x9e3779b9U) ^ *b ^ ((tmp_a << 5) | (tmp_a >> 27));
    *b = tmp_a;
    tmp_b = *a;
    *a = (key + 0x9e3779baU) ^ tmp_a ^ ((tmp_b << 5) | (tmp_b >> 27));
    *b = tmp_b;
    tmp_a = *a;
    *a = (key + 0x9e3779bbU) ^ tmp_b ^ ((tmp_a << 5) | (tmp_a >> 27));
    *b = tmp_a;
    tmp_b = *a;
    *a = (key + 0x9e3779bcU) ^ tmp_a ^ ((tmp_b << 5) | (tmp_b >> 27));
    *b = tmp_b;
    tmp_a = *a;
    *a = (key + 0x9e3779bdU) ^ tmp_b ^ ((tmp_a << 5) | (tmp_a >> 27));
    *b = tmp_a;
    tmp_b = *a;
    *a = (key + 0x9e3779beU) ^ tmp_a ^ ((tmp_b << 5) | (tmp_b >> 27));
    *b = tmp_b;
    tmp_a = *a;
    *a = (key + 0x9e3779bfU) ^ tmp_b ^ ((tmp_a << 5) | (tmp_a >> 27));
    *b = tmp_a;
    tmp_b = *a;
    *a = (key + 0x9e3779c0U) ^ tmp_a ^ ((tmp_b << 5) | (tmp_b >> 27));
    *b = tmp_b;
}

int main(void) {
    stampa_esempio();
    // Esempio di cifratura
du32 x = 0xdeadbeef, y = 0xcafebabe;
    cifra_blocco(&x, &y, 0);
    printf("Risultato cifrato: %08X %08X\n", x, y);
    return 0;
}
