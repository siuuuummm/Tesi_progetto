#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* weak glibc symbol referenced by crti.o _init */
void (*__gmon_start__)(void) __attribute__((weak));

/* 95-byte input string at 0x004011e0 */
static const char s_input_string_004011e0[95] =
    "This is a very long input string that will overflow the buffer and cause undefinfined behavior.";

static char completed_flag;

/* frame_dummy / init array entry: empty body */
void init_array_entry(void)
{
    return;
}

/* register_tm_clones: empty body after optimization */
void register_tm_clones(void)
{
    return;
}

/* deregister_tm_clones: guards the completed flag, then returns */
void deregister_tm_clones(void)
{
    if (completed_flag == '\0') {
        register_tm_clones();
        completed_flag = 1;
        return;
    }
    return;
}

/* frame_dummy (init_array target), called from _init */
void frame_dummy(void)
{
    register_tm_clones();
    return;
}

/* _init / _DT_INIT */
void dt_init(void)
{
    if ((void *)__gmon_start__ != (void *)0x0) {
        ((void (*)(void))__gmon_start__)();
    }
    return;
}

/* _fini / _DT_FINI */
void dt_fini(void)
{
    return;
}

/* copies input into a 72-byte stack buffer and prints it */
void copy_and_print_buffer(char *param_1)
{
    char buffer[72];

    strcpy(buffer, param_1);
    printf("Buffer content: %s\n", buffer);
    return;
}

/* main */
int main(void)
{
    char local_48[8];
    char acStack_40[8];
    char local_38[8];
    char acStack_30[8];
    char local_28[8];
    char acStack_20[8];
    char local_18[8];
    char acStack_10[8];
    char acStack_8[8];
    char uStack0000000000000005[3];
    char uStack000000000000000d[8];

    /* 5 XMM copies of 16 bytes each = 80 bytes at RSP+0..0x4f,
       followed by movups of 16 bytes at RSP+0x4d (bytes 0x4d..0x5c),
       i.e. the 95-byte string at 0x004011e0 copied through RSP+0x4d */
    local_48[0] = s_input_string_004011e0[0];
    local_48[1] = s_input_string_004011e0[1];
    local_48[2] = s_input_string_004011e0[2];
    local_48[3] = s_input_string_004011e0[3];
    local_48[4] = s_input_string_004011e0[4];
    local_48[5] = s_input_string_004011e0[5];
    local_48[6] = s_input_string_004011e0[6];
    local_48[7] = s_input_string_004011e0[7];
    acStack_40[0] = s_input_string_004011e0[8];
    acStack_40[1] = s_input_string_004011e0[9];
    acStack_40[2] = s_input_string_004011e0[10];
    acStack_40[3] = s_input_string_004011e0[11];
    acStack_40[4] = s_input_string_004011e0[12];
    acStack_40[5] = s_input_string_004011e0[13];
    acStack_40[6] = s_input_string_004011e0[14];
    acStack_40[7] = s_input_string_004011e0[15];
    local_38[0] = s_input_string_004011e0[16];
    local_38[1] = s_input_string_004011e0[17];
    local_38[2] = s_input_string_004011e0[18];
    local_38[3] = s_input_string_004011e0[19];
    local_38[4] = s_input_string_004011e0[20];
    local_38[5] = s_input_string_004011e0[21];
    local_38[6] = s_input_string_004011e0[22];
    local_38[7] = s_input_string_004011e0[23];
    acStack_30[0] = s_input_string_004011e0[24];
    acStack_30[1] = s_input_string_004011e0[25];
    acStack_30[2] = s_input_string_004011e0[26];
    acStack_30[3] = s_input_string_004011e0[27];
    acStack_30[4] = s_input_string_004011e0[28];
    acStack_30[5] = s_input_string_004011e0[29];
    acStack_30[6] = s_input_string_004011e0[30];
    acStack_30[7] = s_input_string_004011e0[31];
    local_28[0] = s_input_string_004011e0[32];
    local_28[1] = s_input_string_004011e0[33];
    local_28[2] = s_input_string_004011e0[34];
    local_28[3] = s_input_string_004011e0[35];
    local_28[4] = s_input_string_004011e0[36];
    local_28[5] = s_input_string_004011e0[37];
    local_28[6] = s_input_string_004011e0[38];
    local_28[7] = s_input_string_004011e0[39];
    acStack_20[0] = s_input_string_004011e0[40];
    acStack_20[1] = s_input_string_004011e0[41];
    acStack_20[2] = s_input_string_004011e0[42];
    acStack_20[3] = s_input_string_004011e0[43];
    acStack_20[4] = s_input_string_004011e0[44];
    acStack_20[5] = s_input_string_004011e0[45];
    acStack_20[6] = s_input_string_004011e0[46];
    acStack_20[7] = s_input_string_004011e0[47];
    local_18[0] = s_input_string_004011e0[48];
    local_18[1] = s_input_string_004011e0[49];
    local_18[2] = s_input_string_004011e0[50];
    local_18[3] = s_input_string_004011e0[51];
    local_18[4] = s_input_string_004011e0[52];
    local_18[5] = s_input_string_004011e0[53];
    local_18[6] = s_input_string_004011e0[54];
    local_18[7] = s_input_string_004011e0[55];
    acStack_10[0] = s_input_string_004011e0[56];
    acStack_10[1] = s_input_string_004011e0[57];
    acStack_10[2] = s_input_string_004011e0[58];
    acStack_10[3] = s_input_string_004011e0[59];
    acStack_10[4] = s_input_string_004011e0[60];
    acStack_10[5] = s_input_string_004011e0[61];
    acStack_10[6] = s_input_string_004011e0[62];
    acStack_10[7] = s_input_string_004011e0[63];
    acStack_8[0] = s_input_string_004011e0[64];
    acStack_8[1] = s_input_string_004011e0[65];
    acStack_8[2] = s_input_string_004011e0[66];
    acStack_8[3] = s_input_string_004011e0[67];
    acStack_8[4] = s_input_string_004011e0[68];
    acStack_8[5] = s_input_string_004011e0[69];
    acStack_8[6] = s_input_string_004011e0[70];
    acStack_8[7] = s_input_string_004011e0[71];
    /* block copied with movups to RSP+0x4d: SUB85(...,3) + next 8 bytes */
    uStack0000000000000005[0] = s_input_string_004011e0[80];
    uStack0000000000000005[1] = s_input_string_004011e0[81];
    uStack0000000000000005[2] = s_input_string_004011e0[82];
    uStack000000000000000d[0] = s_input_string_004011e0[88];
    uStack000000000000000d[1] = s_input_string_004011e0[89];
    uStack000000000000000d[2] = s_input_string_004011e0[90];
    uStack000000000000000d[3] = s_input_string_004011e0[91];
    uStack000000000000000d[4] = s_input_string_004011e0[92];
    uStack000000000000000d[5] = s_input_string_004011e0[93];
    uStack000000000000000d[6] = s_input_string_004011e0[94];
    uStack000000000000000d[7] = s_input_string_004011e0[95];

    printf("Buffer content: %s\n", local_48);
    return 0;
}