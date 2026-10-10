#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv)
{
  int iVar1;
  char *__dest;
  long lVar2;
  char *pcVar3;
  uint8_t bVar4;

  bVar4 = 0;
  iVar1 = 1;
  if (2 < argc) {
    setvbuf(stdout, (char *)0x0, 2, 0);
    __dest = (char *)malloc(0x20);
    pcVar3 = __dest;
    for (lVar2 = 8; lVar2 != 0; lVar2 = lVar2 + -1) {
      pcVar3[0] = '\0';
      pcVar3[1] = '\0';
      pcVar3[2] = '\0';
      pcVar3[3] = '\0';
      pcVar3 = pcVar3 + (size_t)bVar4 * (size_t)-8 + 4;
    }
    strncpy(__dest, argv[1], 0x17);
    __dest[0x1c] = -0x18;
    __dest[0x1d] = '\x03';
    __dest[0x1e] = '\0';
    __dest[0x1f] = '\0';
    printf("Sessione %d aperta per %s\n", 1000, __dest);
    iVar1 = strcmp(argv[2], "logout");
    if (iVar1 == 0) {
      free(__dest);
      puts("Logout eseguito");
    }
    if (3 < argc) {
      strtol(argv[3], 0, 10);
    }
    if (*(int *)(__dest + 0x18) == 0) {
      printf("Accesso utente per %s\n", __dest);
    }
    else {
      printf("Accesso amministratore per %s\n", __dest);
    }
    if (iVar1 != 0) {
      free(__dest);
      iVar1 = 0;
    }
  }
  return iVar1;
}
