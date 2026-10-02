#include <stdio.h>

// Costanti identificate nel binario
#define KOCH_DIV            3.0
#define KOCH_MUL_1         0.5
#define KOCH_MUL_2         0.8660254037844386   // ≈ sqrt(3)/2
#define KOCH_X_FINAL      100.0

// Funzione ricorsiva per "disegnare" segmenti (stampa coordinate sul terminale)
void draw_koch_curve_segment(double x1, double y1, double x2, double y2, int depth) {
    if (depth == 0) {
        printf("Linea da (%f,%f) a (%f,%f)\n", x1, y1, x2, y2);
    } else {
        double dx = x2 - x1;
        double dy = y2 - y1;

        double xA = x1 + dx / KOCH_DIV;
        double yA = y1 + dy / KOCH_DIV;

        double xB = x1 + 2 * dx / KOCH_DIV;
        double yB = y1 + 2 * dy / KOCH_DIV;

        // Calcola il punto C (vertex del "triangolo" koch)
        double xC = (xB - xA) * KOCH_MUL_1 + xA - (yB - yA) * KOCH_MUL_2;
        double yC = (xB - xA) * KOCH_MUL_2 + yA + (yB - yA) * KOCH_MUL_1;

        depth--;

        draw_koch_curve_segment(x1, y1, xA, yA, depth);
        draw_koch_curve_segment(xA, yA, xC, yC, depth);
        draw_koch_curve_segment(xC, yC, xB, yB, depth);
        draw_koch_curve_segment(xB, yB, x2, y2, depth);
    }
}

int main(void) {
    // Avvio: da (0,0) a (KOCH_X_FINAL, 0), profondità 3
    draw_koch_curve_segment(0.0, 0.0, KOCH_X_FINAL, 0.0, 3);
    return 0;
}
