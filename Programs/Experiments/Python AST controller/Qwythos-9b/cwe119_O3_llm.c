/*
 * Codice C decompilato da binario stripped
 * Generato automaticamente da analisi Ghidra
 * Ogni funzione è decompilata per nome → indirizzo → disassembly
 * 
 * Fasi svolte:
 *   - list_functions: _DT_INIT, entry, FUN_00400440, FUN_00400470, FUN_004004f0, ...
 *   - entry (0x400430): wrapper di __libc_start_main, contiene il main utente
 *   - FUN_004004f0 (0x4004f0): funzione utente con contenuto decompilato completo
 * 
 * Controlli:
 *   - entry (0x400430):
 *     - MOV EAX,0x403018
 *     - CMP RAX,0x403018
 *     - JZ 0x400460
 *     - MOV EAX,0x0
 *     - TEST RAX,RAX
 *     - JZ 0x400460
 *     - MOV EDI,0x403018
 *     - JMP RAX
 *     (wrapper di libreria, non decompilabile)
 * 
 *   - FUN_00400440 (0x400440):
 *     /* WARNING: Removing unreachable block (ram,0x0040044d) */
 *     /* WARNING: Removing unreachable block (ram,0x00400457) */
 *     void FUN_00400440(void) { return; }
 *     (funzione utente vuota)
 * 
 *   - FUN_00400470 (0x400470):
 *     /* WARNING: Removing unreachable block (ram,0x0040048f) */
 *     /* WARNING: Removing unreachable block (ram,0x00400499) */
 *     void FUN_00400470(void) { return; }
 *     (funzione utente vuota)
 * 
 *   - FUN_004004f0 (0x4004f0):
 *     void FUN_004004f0(char *param_1) {
 *       char acStack_48 [72];
 *       strcpy(acStack_48,param_1);
 *       printf("Buffer content: %s\n",acStack_48);
 *       return;
 *     }
 * 
 *   - strcpy, printf: wrapper di libreria, non decompilabili
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void FUN_00400440(void)
{
    return;
}

static void FUN_00400470(void)
{
    return;
}

static void FUN_004004f0(char *param_1)
{
    char acStack_48[72];

    strcpy(acStack_48, param_1);
    printf("Buffer content: %s\n", acStack_48);
    return;
}

int main(int argc, char **argv)
{
    return 0;
}
