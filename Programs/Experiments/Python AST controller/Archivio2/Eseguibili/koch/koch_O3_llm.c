#include <stdio.h>

// Global variables identified from the binary
double DAT_004011b0 = 1.0; 
double DAT_004011c0 = 0.0; 
double DAT_004011c8 = 0.0; 
double DAT_004011d0 = 0.0; 
double DAT_004011d8 = 0.0; 
double DAT_004011b8 = 0.0; 
double DAT_004011e0 = 1.0; 
double DAT_004011e8 = 1.0; 
double _UNK_004011f8 = 1.0; 
double _DAT_004011f0 = 1.0; 

// Function to print line segments
void print_line_segments(double p1, double p2, double p3, double p4) {
    double dVar1;
    double dVar2;
    double dVar3;
    double dVar4;
    double dVar5;
    double dVar6;

    dVar3 = p3 - p1;
    dVar5 = dVar3 / DAT_004011b0 + p1;
    dVar1 = p4 - p2;
    dVar2 = (dVar3 + dVar3) / DAT_004011b0 + p1;
    dVar6 = dVar1 / DAT_004011b0 + p2;
    dVar1 = (dVar1 + dVar1) / DAT_004011b0 + p2;
    
    dVar3 = ((dVar2 - dVar5) * DAT_004011e0 + dVar5) - (dVar1 - dVar6) * DAT_004011e8;
    dVar4 = (dVar2 - dVar5) * DAT_004011e8 + dVar6 + (dVar1 - dVar6) * DAT_004011e0;

    printf("Linea da (%f,%f) a (%f,%f)\n", p1, p2, dVar5, dVar6);
    printf("Linea da (%f,%f) a (%f,%f)\n", dVar5, dVar6, dVar3, dVar4);
    printf("Linea da (%f,%f) a (%f,%f)\n", dVar3, dVar4, dVar2, dVar1);
    printf("Linea da (%f,%f) a (%f,%f)\n", dVar2, dVar1, p3, p4);
}

// Function to perform calculations and call print_line_segments
void calculate_and_print(double param_1, double param_2, double param_3, double param_4) {
    double dVar1;
    double dVar4;
    double dVar5;
    double dVar6;
    
    double auVar2_0_8 = param_3 - param_1;
    double auVar2_8_8 = param_4 - param_2;
    double auVar7_0_8 = auVar2_0_8 + auVar2_0_8;
    double auVar7_8_8 = auVar2_8_8 + auVar2_8_8;
    
    double auVar3_0_8 = auVar2_0_8 / DAT_004011b0;
    double auVar3_8_8 = auVar2_8_8 / DAT_004011b0;
    
    double auVar8_0_8 = auVar7_0_8 / DAT_004011b0;
    double auVar8_8_8 = auVar7_8_8 / DAT_004011b0;
    
    dVar1 = auVar3_0_8 + param_1;
    dVar4 = auVar3_8_8 + param_2;
    
    double new_p1 = auVar8_0_8 + param_1;
    double new_p2 = auVar8_8_8 + param_2;
    
    dVar6 = (new_p1 - dVar1) * DAT_004011e8 + dVar4 + (new_p2 - dVar4) * _UNK_004011f8;
    dVar5 = ((new_p1 - dVar1) * DAT_004011e0 + dVar1) - (new_p2 - dVar4) * _DAT_004011f0;

    print_line_segments(param_1, param_2, param_3, param_4);
    print_line_segments(dVar1, dVar4, dVar5, dVar6);
    print_line_segments(dVar5, dVar6, new_p1, new_p2);
    print_line_segments(new_p1, new_p2, param_3, param_4);
}

// Main function
int main(void) {
    calculate_and_print(0, 0, 0x4040aaaaaaaaaaab, 0);
    calculate_and_print(DAT_004011c0, 0, 0x4049000000000001, 0x403cde155cb14fdc);
    calculate_and_print(DAT_004011c8, DAT_004011d0, 0x4050aaaaaaaaaaab, 0);
    calculate_and_print(DAT_004011d8, 0, DAT_004011b8, 0);
    return 0;
}
