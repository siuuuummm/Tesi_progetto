#include <stdio.h>
#include <math.h>

// Costanti ricavate dal dump binario (double)
#define DIV3 3.0
#define LEN100 100.0
#define SEG1 32.666666666666664
#define SEG2 50.0
#define SEG3 28.802808943088633
#define SEG4 65.33333333333333
#define HALF 0.5
#define COS30 0.8660254037844387  // cos(30°)
#define SIN30 0.5                // sin(30°)

// Funzione base: stampa 4 segmenti secondo la divisione di koch
void print_koch_lines(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;

    double xA = x1 + dx / DIV3;
    double yA = y1 + dy / DIV3;
    double xB = x1 + 2.0 * dx / DIV3;
    double yB = y1 + 2.0 * dy / DIV3;

    // Calcolo il punto del "picco" equiangolo (rotazione di 60°)
    double px = (xB - xA) * HALF - (yB - yA) * COS30 + xA;
    double py = (xB - xA) * COS30 + (yB - yA) * HALF + yA;

    printf("Linea da (%f,%f) a (%f,%f)\n", x1, y1, xA, yA);
    printf("Linea da (%f,%f) a (%f,%f)\n", xA, yA, px, py);
    printf("Linea da (%f,%f) a (%f,%f)\n", px, py, xB, yB);
    printf("Linea da (%f,%f) a (%f,%f)\n", xB, yB, x2, y2);
}

// Ricorsiva: suddivide il segmento secondo la curva di Koch, stampa quando profondità terminata
void draw_koch_recursive(double x1, double y1, double x2, double y2, int depth) {
    if(depth == 0) {
        printf("Linea da (%f,%f) a (%f,%f)\n", x1, y1, x2, y2);
        return;
    }

    double dx = x2 - x1;
    double dy = y2 - y1;

    double xA = x1 + dx / DIV3;
    double yA = y1 + dy / DIV3;
    double xB = x1 + 2.0 * dx / DIV3;
    double yB = y1 + 2.0 * dy / DIV3;

    double px = (xB - xA) * HALF - (yB - yA) * COS30 + xA;
    double py = (xB - xA) * COS30 + (yB - yA) * HALF + yA;

    draw_koch_recursive(x1, y1, xA, yA, depth - 1);
    draw_koch_recursive(xA, yA, px, py, depth - 1);
    draw_koch_recursive(px, py, xB, yB, depth - 1);
    draw_koch_recursive(xB, yB, x2, y2, depth - 1);
}

// Variante non ricorsiva: richiama solo print koch lines
void draw_koch(double x1, double y1, double x2, double y2) {
    print_koch_lines(x1, y1, x2, y2);
}

int main() {
    // Dal main binario: 4 chiamate a draw_koch con coordinate da costanti binarie
    draw_koch(0.0, 0.0, SEG1, 0.0);
    draw_koch(SEG1, 0.0, SEG2, SEG3);
    draw_koch(SEG2, SEG3, SEG4, 0.0);
    draw_koch(SEG4, 0.0, LEN100, 0.0);
    return 0;
}
