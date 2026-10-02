#include <stdio.h>
#include <string.h>

#define STRING_LITERAL "this is a very long input string that will overflow the buffer and cause undefined behavior."

void FUN_00400476(char *param_1)
{
  char local_48[64];
  strcpy(local_48, param_1);
  printf("Buffer content: %s\n", local_48);
  return;
}

int main(void)
{
  FUN_004004ae((STRING_LITERAL));
  return 0;
}
