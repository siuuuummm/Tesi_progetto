#include <stdio.h>

// Costanti decodificate dalla sezione dati binaria
const double SEG_DIV = 3.0;                // DAT_004011a0
const double FIRST_LEN = 100.0;             // DAT_004011a8
const double SECOND_START_X = 32.666666666666664; // DAT_004011b0
const double THIRD_START_X = 50.0;          // DAT_004011b8
const double THIRD_START_Y = 29.61111111111111;   // DAT_004011c0
const double FOURTH_START_X = 66.66666666666666;  // DAT_004011c8
const double ROTATE1 = 0.5;                 // DAT_004011d0
const double ROTATE2 = 0.491;               // DAT_004011d8

void print_line(double x1, double y1, double x2, double y2) {
    printf("Linea da (%f,%f) a (%f,%f)\n", x1, y1, x2, y2);
}

/// Suddivide un segmento in 4 e ne stampa i sottosegmenti calcolati secondo la logica del binario
void print_segment_split(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double nx = dx / SEG_DIV + x1;
    double ddx = (dx + dx) / SEG_DIV + x1;
    double dy = y2 - y1;
    double ny = dy / SEG_DIV + y1;
    double ddy = (dy + dy) / SEG_DIV + y1;
    double cx = ((ddx - nx) * ROTATE1 + nx) - (ddy - ny) * ROTATE2;
    double cy = (ddx - nx) * ROTATE2 + ny + (ddy - ny) * ROTATE1;

    print_line(x1, y1, nx, ny);
    print_line(nx, ny, cx, cy);
    print_line(cx, cy, ddx, ddy);
    print_line(ddx, ddy, x2, y2);
}

/// Funzione wrapper che semplicemente chiama la divisione in sottosegmenti sui punti dati
void subdivide_and_print_lines(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double mx1 = dx / SEG_DIV + x1;
    double my1 = dy / SEG_DIV + y1;
    double mx2 = (dx + dx) / SEG_DIV + x1;
    double my2 = (dy + dy) / SEG_DIV + y1;
    double cx = ((mx2 - mx1) * ROTATE1 + mx1) - (my2 - my1) * ROTATE2;
    double cy = (mx2 - mx1) * ROTATE2 + my1 + (my2 - my1) * ROTATE1;

    print_segment_split( x1,  y1,  mx1,  my1);
    print_segment_split( mx1, my1, cx, cy);
    print_segment_split( cx, cy, mx2, my2);
    print_segment_split( mx2, my2, x2, y2);
}

// Funzione equivalente al main utente trovata nel binario
int main(void) {
    subdivide_and_print_lines(0, 0, 0, FIRST_LEN);
    subdivide_and_print_lines(SECOND_START_X, 0, THIRD_START_X, THIRD_START_Y);
    subdivide_and_print_lines(FOURTH_START_X, 0, SECOND_START_X, 0);
    subdivide_and_print_lines(0, 0, 0, FIRST_LEN);
    return 0;
}
