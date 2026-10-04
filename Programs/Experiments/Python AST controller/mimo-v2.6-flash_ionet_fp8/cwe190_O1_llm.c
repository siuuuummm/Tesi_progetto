#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  unsigned int count;
  int limit;
  int step;
  int *buffer;
  int status;
  int *cursor;

  if (1 < argc) {
    setvbuf(stdout, (char *)0x0, 2, 0);
    count = (unsigned int)strtol(argv[1], 0, 10);
    if (count < 0x65) {
      buffer = (int *)malloc((unsigned long)(count * 4 & 0xff));
      printf("Elementi: %u, byte allocati: %u\n",
             (unsigned long)count, (unsigned long)(count * 4 & 0xff));
      if (count != 0) {
        limit = count * 3;
        step = 1;
        count = 0;
        cursor = buffer;
        do {
          *cursor = step;
          count = count + step;
          step = step + 3;
          cursor = cursor + 1;
        } while (step != limit + 1);
      }
      printf("Somma: %u\n", (unsigned long)count);
      free(buffer);
      status = 0;
    }
    else {
      puts("Troppi elementi");
      status = 1;
    }
    return status;
  }
  return 1;
}