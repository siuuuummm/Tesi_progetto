#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/* main (entry) - wrapped entry point */
void main(void)
{
  FUN_00400360();
  return;
}

/* init_call (FUN_00400360) */
void FUN_00400360(void)
{
  (*(void (*)())0x00402ff8)();
  return;
}

/* FUN_004003c0 */
void FUN_004003c0(void)
{
  return;
}

/* FUN_00400400 */
void FUN_00400400(void)
{
  return;
}

/* print_buffer (FUN_00400476) */
void FUN_00400476(char *param_1)
{
  char local_48 [64];

  strcpy(local_48,param_1);
  printf("Buffer content: %s\n",local_48);
  return;
}

/* trigger_overflow (FUN_004004ae) */
uint64_t FUN_004004ae(void)
{
  FUN_00400476(
              "This is a very long input string that will overflow the buffer and cause undefined behavior."
              );
  return 0;
}
