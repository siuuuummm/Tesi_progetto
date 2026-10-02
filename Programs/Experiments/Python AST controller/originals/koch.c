#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

void draw_koch(Point a, Point b, int limit) {
    if (limit == 0) {
        printf("Linea da (%f,%f) a (%f,%f)\n", a.x, a.y, b.x, b.y);
        return;
    }

    Point s, v, t;
    // Dividiamo il segmento in tre parti
    s.x = a.x + (b.x - a.x) / 3.0;
    s.y = a.y + (b.y - a.y) / 3.0;
    t.x = a.x + 2.0 * (b.x - a.x) / 3.0;
    t.y = a.y + 2.0 * (b.y - a.y) / 3.0;

    // Calcoliamo il vertice del triangolo equilatero (v)
    double angle = 60.0 * M_PI / 180.0;
    v.x = s.x + (t.x - s.x) * cos(angle) - (t.y - s.y) * sin(angle);
    v.y = s.y + (t.x - s.x) * sin(angle) + (t.y - s.y) * cos(angle);

    draw_koch(a, s, limit - 1);
    draw_koch(s, v, limit - 1);
    draw_koch(v, t, limit - 1);
    draw_koch(t, b, limit - 1);
}

int main() {
    Point p1 = {0.0, 0.0};
    Point p2 = {100.0, 0.0};
    draw_koch(p1, p2, 3);
    return 0;
}
