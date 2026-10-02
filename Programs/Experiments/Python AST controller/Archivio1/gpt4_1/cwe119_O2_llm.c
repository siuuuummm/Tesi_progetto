#include <stdio.h>
#include <string.h>

// Funzione vulnerabile a buffer overflow
void vulnerable_function(const char *input) {
    char buffer[72];
    strcpy(buffer, input);  // Nessun controllo sulla lunghezza, overflow possibile!
    printf("Buffer content: %s\n", buffer);
}

int main() {
    // Stringa lunga che causerà overflow nel buffer
    const char *dangerous_input = 
        "This is a very long input string that will overflow the buffer and cause undefined behavior.";
    vulnerable_function(dangerous_input);
    return 0;
}
