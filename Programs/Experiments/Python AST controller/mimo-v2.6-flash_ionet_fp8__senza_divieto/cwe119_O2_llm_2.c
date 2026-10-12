#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* GOT/data location referenced by compiler-generated frame dummy helpers
   (decompiled as literal 0x403018 in FUN_004003f0 / FUN_00400420). */
#define FRAME_DUMMY_TARGET 0x403018

/* DAT_00403014: one-shot guard byte used by FUN_004003f0 */
static char DAT_00403014;

/* FUN_004003f0 - frame dummy, decompiled as an empty body
   (the guard/indirect-call blocks are marked unreachable by the decompiler). */
void FUN_004003f0(void)
{
    return;
}

/* FUN_00400420 - register frame dummy / DT_INIT helper, empty after
   unreachable-block removal. */
void FUN_00400420(void)
{
    return;
}

/* FUN_004003e0 - empty ENDBR64 stub present in .text */
void FUN_004003e0(void)
{
    return;
}

/* FUN_004004a0 - copies param_1 into a 72-byte stack buffer with strcpy
   (unbounded) and prints it. */
void FUN_004004a0(char *param_1)
{
    char acStack_48[72];

    strcpy(acStack_48, param_1);
    printf("Buffer content: %s\n", acStack_48);
    return;
}

/* FUN_00400390 - program entry passed to __libc_start_main (the "main"). */
int FUN_00400390(void)
{
    FUN_004004a0(
        "This is a very long input string that will overflow the buffer and cause undefined behavior."
    );
    return 0;
}

/* _INIT_0 - .init_array element that runs FUN_00400420 */
void _INIT_0(void)
{
    FUN_00400420();
    return;
}

/* _FINI_0 - .fini_array element guarding a single call to FUN_004003f0 */
void _FINI_0(void)
{
    if (DAT_00403014 == '\0') {
        FUN_004003f0();
        DAT_00403014 = 1;
        return;
    }
    return;
}

/* _DT_INIT - calls __gmon_start__ through the GOT when non-NULL */
void _DT_INIT(void)
{
    if ((void *)0 != (void *)0) {
        /* decompiled condition: PTR___gmon_start___00402fe0 != 0 */
    }
    return;
}

/* _DT_FINI - empty */
void _DT_FINI(void)
{
    return;
}

/* FUN_00400360 - PLT stub shape preserved from the binary:
   push qword ptr [0x00402ff0]; jmp qword ptr [0x00402ff8] */
void FUN_00400360(void)
{
    return;
}