#include <stdio.h>
#include <string.h>

// Funzione che prende una stringa, la copia in un buffer di dimensione fissa e la stampa
void print_buffer_content(const char *input) {
    char buffer[64];
    strcpy(buffer, input); 
    printf("Buffer content: %s\n", buffer);
}

// Funzione main reale ricostruita dal binario
int main(void) {
    print_buffer_content(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}
