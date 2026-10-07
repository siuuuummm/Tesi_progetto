#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void log_print(char *param_1)
{
  printf(param_1);
  putchar(10);
  return;
}

int main(int argc, char *argv[])
{
  int iVar;

  iVar = argc < 2;
  if (iVar) {
    printf("Uso: %s <messaggio>\n", "logger");
  }
  else {
    printf("[log] ");
    printf(argv[1]);
    putchar(10);
  }
  return iVar;
}
