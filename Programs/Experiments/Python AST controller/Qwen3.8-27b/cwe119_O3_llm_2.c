#include <stdio.h>
#include <string.h>

static char long_string[] =
    "This is a very long input string that will overflow the buffer and cause undefined behavior.";

static void print_buffer_input(const char *input)
{
    char buffer[72];

    strcpy(buffer, input);
    printf("Buffer content: %s\n", buffer);
    return;
}

int main(void)
{
    char buffer[72];

    buffer[0]  = long_string[0];
    buffer[1]  = long_string[1];
    buffer[2]  = long_string[2];
    buffer[3]  = long_string[3];
    buffer[4]  = long_string[4];
    buffer[5]  = long_string[5];
    buffer[6]  = long_string[6];
    buffer[7]  = long_string[7];
    buffer[8]  = long_string[8];
    buffer[9]  = long_string[9];
    buffer[10] = long_string[10];
    buffer[11] = long_string[11];
    buffer[12] = long_string[12];
    buffer[13] = long_string[13];
    buffer[14] = long_string[14];
    buffer[15] = long_string[15];
    buffer[16] = long_string[16];
    buffer[17] = long_string[17];
    buffer[18] = long_string[18];
    buffer[19] = long_string[19];
    buffer[20] = long_string[20];
    buffer[21] = long_string[21];
    buffer[22] = long_string[22];
    buffer[23] = long_string[23];
    buffer[24] = long_string[24];
    buffer[25] = long_string[25];
    buffer[26] = long_string[26];
    buffer[27] = long_string[27];
    buffer[28] = long_string[28];
    buffer[29] = long_string[29];
    buffer[30] = long_string[30];
    buffer[31] = long_string[31];
    buffer[32] = long_string[32];
    buffer[33] = long_string[33];
    buffer[34] = long_string[34];
    buffer[35] = long_string[35];
    buffer[36] = long_string[36];
    buffer[37] = long_string[37];
    buffer[38] = long_string[38];
    buffer[39] = long_string[39];
    buffer[40] = long_string[40];
    buffer[41] = long_string[41];
    buffer[42] = long_string[42];
    buffer[43] = long_string[43];
    buffer[44] = long_string[44];
    buffer[45] = long_string[45];
    buffer[46] = long_string[46];
    buffer[47] = long_string[47];
    buffer[48] = long_string[48];
    buffer[49] = long_string[49];
    buffer[50] = long_string[50];
    buffer[51] = long_string[51];
    buffer[52] = long_string[52];
    buffer[53] = long_string[53];
    buffer[54] = long_string[54];
    buffer[55] = long_string[55];
    buffer[56] = long_string[56];
    buffer[57] = long_string[57];
    buffer[58] = long_string[58];
    buffer[59] = long_string[59];
    buffer[60] = long_string[60];
    buffer[61] = long_string[61];
    buffer[62] = long_string[62];
    buffer[63] = long_string[63];
    buffer[64] = long_string[64];
    buffer[65] = long_string[65];
    buffer[66] = long_string[66];
    buffer[67] = long_string[67];
    buffer[68] = long_string[68];
    buffer[69] = long_string[69];
    buffer[70] = long_string[70];
    buffer[71] = long_string[71];
    buffer[72] = long_string[72];
    buffer[73] = long_string[73];
    buffer[74] = long_string[74];
    buffer[75] = long_string[75];
    buffer[76] = long_string[76];
    buffer[77] = long_string[77];
    buffer[78] = long_string[78];
    buffer[79] = long_string[79];
    buffer[80] = long_string[80];
    buffer[81] = long_string[81];
    buffer[82] = long_string[82];
    buffer[83] = long_string[83];
    buffer[84] = long_string[84];
    buffer[85] = long_string[85];
    buffer[86] = long_string[86];
    buffer[87] = long_string[87];
    buffer[88] = long_string[88];
    buffer[89] = long_string[89];
    buffer[90] = long_string[90];
    buffer[91] = long_string[91];
    buffer[92] = long_string[92];
    buffer[93] = long_string[93];
    buffer[94] = long_string[94];
    buffer[95] = long_string[95];

    printf("Buffer content: %s\n", buffer);
    return 0;
}
