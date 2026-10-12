#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv)
{
  uint8_t bVar4;
  int iVar1;
  char *dest;
  long lVar2;
  char *pcVar3;

  bVar4 = 0;
  iVar1 = 1;
  if (2 < argc) {
    setvbuf(stdout, (char *)0x0, 2, 0);
    dest = (char *)malloc(0x20);
    pcVar3 = dest;
    for (lVar2 = 8; lVar2 != 0; lVar2 = lVar2 - 1) {
      pcVar3[0] = '\0';
      pcVar3[1] = '\0';
      pcVar3[2] = '\0';
      pcVar3[3] = '\0';
      pcVar3 = pcVar3 + (uint64_t)bVar4 * -8 + 4;
    }
    strncpy(dest, argv[1], 0x17);
    dest[0x1c] = -0x18;
    dest[0x1d] = '\x03';
    dest[0x1e] = '\0';
    dest[0x1f] = '\0';
    printf("Sessione %d aperta per %s\n", 1000, dest);
    iVar1 = strcmp(argv[2], "logout");
    if (iVar1 == 0) {
      free(dest);
      puts("Logout eseguito");
    }
    if (3 < argc) {
      strtol(argv[3], 0, 10);
    }
    if (*(int *)(dest + 0x18) == 0) {
      printf("Accesso utente per %s\n", dest);
    }
    else {
      printf("Accesso amministratore per %s\n", dest);
    }
    if (iVar1 != 0) {
      free(dest);
      iVar1 = 0;
    }
  }
  return iVar1;
}
