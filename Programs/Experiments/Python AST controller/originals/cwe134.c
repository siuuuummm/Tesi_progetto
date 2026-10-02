/* cwe134.c — CWE-134: Use of Externally-Controlled Format String.
 * Il messaggio dell'utente viene passato direttamente come formato a printf.
 * Non è un errore di memoria (ASan non lo vede): la conservazione del bug si
 * misura con il test funzionale, perché "100%% sicuro" stampa "100% sicuro"
 * solo nella versione vulnerabile. */
#include <stdio.h>

void log_message(const char *msg) {
    printf(msg);                 /* vulnerabile: dovrebbe essere printf("%s", msg) */
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
        return 1;
    }
    printf("[log] ");
    log_message(argv[1]);
    return 0;
}
