#include <stdio.h>
#include <stdint.h>

/*
 * Reconstructed from binary: test_O2 (stripped, x86-64, compiled with gcc 15.3.1 -O2)
 *
 * entry -> __libc_start_main(FUN_00400390, ...)  =>  main == FUN_00400390
 *
 * main only references the imported printf (PLT 0x00400380) and putchar
 * (PLT 0x00400370). No other program-defined function is reachable from main;
 * the remaining FUN_* symbols are compiler-generated startup/teardown code.
 *
 * Disassembly of FUN_00400390:
 *   sub  rsp,0x18
 *   cmp  edi,1            ; argc <= 1 ?
 *   jle  0x4003cb
 *   mov  edi,0x4011dc     ; "[log] "
 *   mov  [rsp+8],rsi      ; save argv
 *   call 0x400380         ; printf("[log] ")
 *   mov  rsi,[rsp+8]
 *   mov  rdi,[rsi+8]      ; argv[1]
 *   call 0x400380         ; printf(argv[1])
 *   mov  edi,0xa          ; 10
 *   call 0x400370         ; putchar(10)
 *   xor  eax,eax          ; return 0
 *   add  rsp,0x18
 *   ret
 *   0x4003cb:
 *   mov  esi,0x4011c0     ; "logger"
 *   mov  edi,0x4011c7     ; "Uso: %s <messaggio>\n"
 *   call 0x400380         ; printf("Uso: %s <messaggio>\n", "logger")
 *   mov  eax,1            ; return 1
 *   jmp  0x4003c6
 */
int main(int param_1, char **param_2)
{
  if (param_1 < 2) {
    printf("Uso: %s <messaggio>\n", "logger");
  }
  else {
    printf("[log] ");
    printf(*(char **)(param_2 + 8));
    putchar(10);
  }
  return param_1 < 2;
}
