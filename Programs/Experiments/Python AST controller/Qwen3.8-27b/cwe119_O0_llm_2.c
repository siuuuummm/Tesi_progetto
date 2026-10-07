#include <stdio.h>
#include <string.h>

/*
 * FUN_00400476
 * Coda lo stringa in ingresso in un buffer locale di 64 byte (char local_48[64])
 * e ne stampa il contenuto. La copia avviene tramite strcpy senza controlli
 * sulla lunghezza: con input lunghi si ha overflow dello stack.
 */
void print_buffer(char *param_1)
{
  char local_48[64];

  strcpy(local_48,param_1);
  printf("Buffer content: %s\n",local_48);
  return;
}

/*
 * FUN_004004ae
 * main: chiama print_buffer con una stringa lunga (92 byte + terminatore)
 * destinata all'indirizzo 0x4011d8 nel segmento .rodata, poi restituisce 0.
 */
int main(void)
{
  print_buffer("This is a very long input string that will overflow the buffer and cause undefined behavior.");
  return 0;
}
