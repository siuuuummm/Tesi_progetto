#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
 * Decompilation notes:
 * - entry() is the program entry point; it calls the main loop function via a resolved symbol.
 * - FUN_00400500() is the main loop function, called from entry().
 * - FUN_00400590() is a helper used by FUN_00400500() for data processing.
 */

/* Data constants extracted directly from binary:
 * - 0x4141414141414141ULL (8 bytes)
 * - 0x1001001001001001ULL (8 bytes)
 * - 0x0102030405060708ULL (8 bytes)
 * - 0x0001020304050607ULL (8 bytes)
 * - 0x0000000000000000ULL (8 bytes)
 */
static uint64_t DATA_A = 0x4141414141414141ULL;
static uint64_t DATA_B = 0x1001001001001001ULL;
static uint64_t DATA_C = 0x0102030405060708ULL;
static uint64_t DATA_D = 0x0001020304050607ULL;
static uint64_t DATA_E = 0x0000000000000000ULL;

/* Main loop function: processes data using helper FUN_00400590.
 * Invokes FUN_00400590 in a loop, then calls printf and exits.
 * The exact behavior of FUN_00400590() is preserved from decompiled output.
 */
static void FUN_00400500(void)
{
    uint64_t param_1;
    uint64_t param_2;
    uint64_t param_3;
    uint64_t param_4;

    /* Retrieve DATA_A */
    param_1 = DATA_A;

    /* Retrieve DATA_B */
    param_2 = DATA_B;

    /* Retrieve DATA_C */
    param_3 = DATA_C;

    /* Retrieve DATA_D */
    param_4 = DATA_D;

    /* Call FUN_00400590 with all parameters */
    FUN_00400590(param_1, param_2, param_3, param_4);
}

/* Helper function: processes data using constant DATA_E and DATA_D.
 * Performs arithmetic operations and prints results via printf.
 * The exact arithmetic is preserved from decompiled output:
 *   (DATA_E + param_1) * param_2 + param_3
 *   (DATA_E + param_1) * param_2 + param_3 + param_4
 *   param_1 * param_2 * param_3
 * Prints each result on separate lines.
 */
static void FUN_00400590(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4)
{
    uint64_t param_5;
    uint64_t param_6;
    uint64_t param_7;
    uint64_t param_8;
    uint64_t param_9;
    uint64_t param_10;

    /* Retrieve DATA_E */
    param_5 = DATA_E;

    /* Add param_1 to DATA_E */
    param_6 = param_5 + param_1;

    /* Multiply result by param_2 */
    param_7 = param_6 * param_2;

    /* Add param_3 */
    param_8 = param_7 + param_3;

    /* Call FUN_00400500 with param_8 */
    FUN_00400500(param_8);

    /* Add param_4 */
    param_9 = param_8 + param_4;

    /* Multiply result by param_2 */
    param_10 = param_9 * param_2;

    /* Print first result */
    printf("%d\n", param_10);

    /* Print second result */
    printf("%d\n", param_8);

    /* Multiply param_1 by param_2 */
    param_6 = param_1 * param_2;

    /* Multiply result by param_3 */
    param_7 = param_6 * param_3;

    /* Print third result */
    printf("%d\n", param_7);

    /* Print DATA_D */
    printf("%d\n", param_4);

    /* Exit */
    exit(0);
}

/* Entry point: resolves and calls FUN_00400500.
 * This is the main function entry point; it invokes FUN_00400500() after
 * resolving the function pointer. The exact resolution logic is preserved.
 */
static void FUN_00400780(void)
{
    uint64_t param_1;

    /* Resolve and call FUN_00400500 */
    param_1 = (uint64_t)FUN_00400500;
    FUN_00400500();
}

/* Global entry point: calls FUN_00400780 and returns 0.
 * This is the actual program entry point; it invokes FUN_00400780() and
 * returns 0. The exact behavior is preserved from decompiled output.
 */
int entry(void)
{
    FUN_00400780();
    return 0;
}

int main(int argc, char **argv)
{
    entry();
    return 0;
}
