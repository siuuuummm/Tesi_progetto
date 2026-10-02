#include <stdio.h>

// Costanti dedotte dai dati binari (aggiorna se necessario)
#define FRAC_CONST_3 3.0
// Placeholder per le altre costanti estratte da dati globali
double FRAC_CONST_B = 1.0; // Es. _DAT_004011b0
double FRAC_CONST_BX = 1.0; // Es. _UNK_004011b8
double FRAC_CONST_C = 1.0; // Es. _DAT_004011c0
double FRAC_CONST_CX = 1.0; // Es. _UNK_004011c8

/*
 * Ricorsivamente disegna una "curva frattale" (forse Dragon Curve o Koch)
 * Suddivide il segmento e stampa ricorsivamente i sottosegmenti
 */
void draw_fractal(double x0, double y0, double x1, double y1, int depth) {
    if (depth == 0) {
        printf("Linea da (%f,%f) a (%f,%f)\n", x0, y0, x1, y1);
        return;
    }
    // Vettore tra i punti
    double dx = x1 - x0, dy = y1 - y0;
    // Nuovi punti intermedi (ipotizzando costanti di trasformazione)
    double mx = x0 + dx / FRAC_CONST_3;
    double my = y0 + dy / FRAC_CONST_3;
    double nx = x0 + 2*dx / FRAC_CONST_3;
    double ny = y0 + 2*dy / FRAC_CONST_3;
    // Rotazione o "piega" sul segmento centrale (costanti placeholder)
    double px = ((nx - mx) * FRAC_CONST_B + mx) - (ny - my) * FRAC_CONST_C;
    double py = (nx - mx) * FRAC_CONST_BX + my + (ny - my) * FRAC_CONST_CX;

    // Ricorsione sui 4 segmenti (modifica a 3 se necessario dopo verifica costanti)
    draw_fractal(x0, y0, mx, my, depth - 1);
    draw_fractal(mx, my, px, py, depth - 1);
    draw_fractal(px, py, nx, ny, depth - 1);
    draw_fractal(nx, ny, x1, y1, depth - 1);
}

int main() {
    // Chiamata iniziale, ripristina valori dai parametri usati in binario
    double x0 = 0.0, y0 = 0.0, x1 = 100.0, y1 = 0.0; // x1: 0x4059000000000000 = 100.0
    int depth = 3;
    draw_fractal(x0, y0, x1, y1, depth);
    return 0;
}
