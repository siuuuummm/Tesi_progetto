#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int iVar1;
  char *buffer;
  long i;
  char *p;
  uint8_t bVar4;

  bVar4 = 0;
  iVar1 = 1;
  if (argc > 2) {
    setvbuf(stdout, (char *)0, 2, 0);
    buffer = (char *)malloc(0x20);
    p = buffer;
    for (i = 8; i != 0; i = i + -1) {
      p[0] = '\0';
      p[1] = '\0';
      p[2] = '\0';
      p[3] = '\0';
      p = p + (uint64_t)bVar4 * -8 + 4;
    }
    strncpy(buffer, argv[1], 0x17);
    buffer[0x1c] = (char)(-0x18);
    buffer[0x1d] = '\x03';
    buffer[0x1e] = '\0';
    buffer[0x1f] = '\0';
    printf("Sessione %d aperta per %s\n", 1000, buffer);
    iVar1 = strcmp(argv[2], "logout");
    if (iVar1 == 0) {
      free(buffer);
      puts("Logout eseguito");
    }
    if (argc > 3) {
      strtol(argv[3], 0, 10);
    }
    if (*(int *)(buffer + 0x18) == 0) {
      printf("Accesso utente per %s\n", buffer);
    }
    else {
      printf("Accesso amministratore per %s\n", buffer);
    }
    if (iVar1 != 0) {
      free(buffer);
      iVar1 = 0;
    }
  }
  return iVar1;
}
