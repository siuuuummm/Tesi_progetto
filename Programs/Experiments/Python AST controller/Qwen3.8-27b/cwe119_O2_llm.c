#include <stdio.h>
#include <string.h>

void copy_and_print(char *input)
{
  char buf[72];

  strcpy(buf, input);
  printf("Buffer content: %s\n", buf);
  return;
}

int main(void)
{
  copy_and_print("This is a very long input string that will overflow the buffer and cause undefined behavior.");
  return 0;
}
