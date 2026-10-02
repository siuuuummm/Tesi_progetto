#include <stdio.h>
#include <math.h>

// Dati globali ricostruiti dai parametri osservati nel binario
static const double subdivision_factor = 3.0;    // DAT_00401230 (verificare correttezza reale)
static const double rotation_angle = 1.3925;     // DAT_00401238 (valore di esempio coerente con logica fractal/koch)
static const double initial_length = 100.0;      // DAT_00401240 (presumibile a vista)

// Funzione ricorsiva che suddivide e stampa i segmenti di una linea (tipo curva di Koch, per esempio)
void draw_fractal_line(double x1, double y1, double x2, double y2, int depth) {
    if (depth == 0) {
        printf("Linea da (%f,%f) a (%f,%f)\n", x1, y1, x2, y2);
    } else {
        double xA = (x2 - x1) / subdivision_factor + x1;
        double yA = (y2 - y1) / subdivision_factor + y1;
        double xB = ((x2 - x1) * 2) / subdivision_factor + x1;
        double yB = ((y2 - y1) * 2) / subdivision_factor + y1;

        double xp, yp;
        // Calcolo punto ruotato (rotazione di un segmento secondo angolo fissato rotation_angle)
        xp = (cos(rotation_angle) * (xB - xA) + xA) - (yB - yA) * sin(rotation_angle);
        yp = sin(rotation_angle) * (xB - xA) + cos(rotation_angle) * (yB - yA) + yA;

        draw_fractal_line(x1, y1, xA, yA, depth - 1);
        draw_fractal_line(xA, yA, xp, yp, depth - 1);
        draw_fractal_line(xp, yp, xB, yB, depth - 1);
        draw_fractal_line(xB, yB, x2, y2, depth - 1);
    }
}

int main(void) {
    // Parametri di chiamata osservati dall'entrypoint: draw_fractal_line(0, 0, initial_length, 0, 3)
    draw_fractal_line(0, 0, initial_length, 0, 3);
    return 0;
}
