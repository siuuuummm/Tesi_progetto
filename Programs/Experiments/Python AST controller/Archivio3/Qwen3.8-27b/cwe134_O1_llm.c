#include <stdio.h>

void print_message(char *msg)
{
  printf(msg);
  putchar(10);
  return;
}

int main(int argc, char **argv)
{
  if (argc < 2) {
    printf("Uso: %s <messaggio>\n", "logger");
  }
  else {
    printf("[log] ");
    print_message(argv[1]);
  }
  return argc < 2;
}
