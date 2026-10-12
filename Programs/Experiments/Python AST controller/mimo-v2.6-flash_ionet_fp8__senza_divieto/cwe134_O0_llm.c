#include <stdio.h>

/* FUN_00400476: stampa il messaggio passato come stringa di formato,
   poi un newline */
void print_message(char *msg)
{
    printf(msg);
    putchar(10);
}

/* FUN_004004a0: main - se manca l'argomento mostra l'uso,
   altrimenti prefissa "[log]" e stampa il messaggio */
int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Uso: %s <messaggio>\n", "logger");
    } else {
        printf("[log] ");
        print_message(*(argv + 1));
    }
    return argc < 2;
}