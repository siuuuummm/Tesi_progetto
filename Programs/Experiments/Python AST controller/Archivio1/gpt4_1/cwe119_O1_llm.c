#include <stdio.h>
#include <string.h>

// Funzione vulnerabile: copia una stringa in un buffer locale e stampa il buffer
void print_buffer(const char *input) {
    char buffer[64];
    strcpy(buffer, input); // overflow!
    printf("Buffer content: %s\n", buffer);
}

// Funzione "main" del binario
int main(void) {
    print_buffer("This is a very long input string that will overflow the buffer and cause undefined behavior.");
    return 0;
}
