#include <stdio.h>

/**
 * Recursive function to draw a Koch curve.
 * 
 * @param x1      Starting X coordinate
 * @param y1      Starting Y coordinate
 * @param x2      Ending X coordinate
 * @param y2      Ending Y coordinate
 * @param depth   Recursion depth (order of the fractal)
 */
void draw_koch_curve(double x1, double y1, double x2, double y2, int depth) {
    if (depth == 0) {
        // Base case: draw a straight line between the two points
        printf("Linea da (%f,%f) a (%f,%f)\n", x1, y1, x2, y2);
    } else {
        // Constants for the Koch curve
        const double ONE_THIRD = 1.0 / 3.0;
        const double TWO_THIRD = 2.0 / 3.0;
        const double COS60 = 0.5;
        const double SIN60 = 0.86602540378;

        double dx = x2 - x1;
        double dy = y2 - y1;

        // Point A: 1/3 along the segment
        double ax = x1 + dx * ONE_THIRD;
        double ay = y1 + dy * ONE_THIRD;

        // Point B: 2/3 along the segment
        double bx = x1 + dx * TWO_THIRD;
        double by = y1 + dy * TWO_THIRD;

        // Point C: The peak of the triangle
        // Calculated by rotating vector AB by 60 degrees around point A
        double cx = (bx - ax) * COS60 - (by - ay) * SIN60 + ax;
        double cy = (bx - ax) * SIN60 + (by - ay) * COS60 + ay;

        // Recursive calls for the four new segments
        draw_koch_curve(x1, y1, ax, ay, depth - 1);
        draw_koch_curve(ax, ay, cx, cy, depth - 1);
        draw_koch_curve(cx, cy, bx, by, depth - 1);
        draw_koch_curve(bx, by, x2, y2, depth - 1);
    }
}

int main(void) {
    // Initial call to draw a Koch curve from (0,0) to (100,0) with depth 3
    draw_koch_curve(0.0, 0.0, 100.0, 0.0, 3);
    return 0;
}
