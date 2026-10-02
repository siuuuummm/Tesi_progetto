#include <stdio.h>

// Costanti globali estratte dai dati
static const double STEP = 3.0;              // DAT_004011a0: 0x4008000000000000 = 3.0
static const double ROT_CONST_1 = 0.5;       // DAT_004011d0: 0x3fe0000000000001 ~ 0.5
static const double ROT_CONST_2 = 0.986;     // DAT_004011d8: 0x3febB67AE8584CAA ~ 0.986
// I valori restanti vengono presi come placeholder (da mappare accuratamente su dati reali estratti da Ghidra)
static const double GLOBAL1 = 42.0;     // DAT_004011a8
static const double GLOBAL2 = 32.0;     // DAT_004011b0
static const double GLOBAL3 = 50.0;     // DAT_004011b8
static const double GLOBAL4 = 12.0;     // DAT_004011c0
static const double GLOBAL5 = 99.0;     // DAT_004011c8
static const double EXTRA1 = 0.0;       // _UNK_004011e8
static const double EXTRA2 = 0.0;       // _DAT_004011e0
//

// Stampa i quattro segmenti che compongono un dato tratto secondo una suddivisione geometrica
void print_square_segments(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double mx1 = dx / STEP + x1;
    double mx2 = (dx + dx) / STEP + x1;
    double dy = y2 - y1;
    double my1 = dy / STEP + y1;
    double my2 = (dy + dy) / STEP + y1;
    double px = ((mx2 - mx1) * ROT_CONST_1 + mx1) - (my2 - my1) * ROT_CONST_2;
    double py = (mx2 - mx1) * ROT_CONST_2 + my1 + (my2 - my1) * ROT_CONST_1;
    printf("Linea da (%f,%f) a (%f,%f)\n", x1, y1, mx1, my1);
    printf("Linea da (%f,%f) a (%f,%f)\n", mx1, my1, px, py);
    printf("Linea da (%f,%f) a (%f,%f)\n", px, py, mx2, my2);
    printf("Linea da (%f,%f) a (%f,%f)\n", mx2, my2, x2, y2);
}

// Ricorsiva: Dato un segmento, lo suddivide e richiama su sotto-segmenti
void draw_fractal(double x1, double y1, double x2, double y2, int depth) {
    if (depth == 0) {
        printf("Linea da (%f,%f) a (%f,%f)\n", x1, y1, x2, y2);
        return;
    }
    double dx = x2 - x1;
    double dy = y2 - y1;
    double mx1 = dx / STEP + x1;
    double mx2 = (dx + dx) / STEP + x1;
    double my1 = dy / STEP + y1;
    double my2 = (dy + dy) / STEP + y1;
    double px = ((mx2 - mx1) * ROT_CONST_1 + mx1) - (my2 - my1) * EXTRA2;
    double py = (mx2 - mx1) * ROT_CONST_2 + my1 + (my2 - my1) * EXTRA1;
    draw_fractal(x1, y1, mx1, my1, depth - 1);
    draw_fractal(mx1, my1, px, py, depth - 1);
    draw_fractal(px, py, mx2, my2, depth - 1);
    draw_fractal(mx2, my2, x2, y2, depth - 1);
}

// Funzione usata dal main per stampare 4 segmenti ben precisi (dati da costanti/glob)
void fractal_entrypoint() {
    // Parametri e valori costanti ricreati da chiamate e dati
    print_square_segments(0, 0, GLOBAL2); // Prima chiamata: fake parametri raccolti
    print_square_segments(GLOBAL2, 0, GLOBAL3, GLOBAL4); // Parametri presi da struttura dati
    print_square_segments(GLOBAL3, GLOBAL4, GLOBAL5, 0); // Altro blocco dati
    print_square_segments(GLOBAL4, 0, GLOBAL1); // Ultimi
}

int main() {
    // Dalla main decompilata:
    fractal_entrypoint();
    return 0;
}
