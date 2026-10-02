#include <stdio.h>

/**
 * This program implements the Koch Curve fractal.
 * It recursively divides a line segment into four smaller segments,
 * creating a "spike" in the middle.
 */

void draw_koch_curve(double x1, double y1, double x2, double y2, int depth) {
    if (depth == 0) {
        // Base case: print the line segment
        printf("Linea da (%f,%f) a (%f,%f)\n", x1, y1, x2, y2);
    } else {
        // Calculate the vector of the current segment
        double dx = x2 - x1;
        double dy = y2 - y1;

        // First point of the division (1/3 of the way)
        double x_third = x1 + dx / 3.0;
        double y_third = y1 + dy / 3.0;

        // Second point of the division (2/3 of the way)
        double x_two_third = x1 + 2.0 * dx / 3.0;
        double y_two_third = y1 + 2.0 * dy / 3.0;

        // Calculate the peak point using a 60-degree rotation
        // The constants 0.5 and 0.86602540378 correspond to cos(60°) and sin(60°)
        double peak_x = (x_two_third - x_third) * 0.5 + x_third - (y_two_third - y_third) * 0.86602540378;
        double peak_y = (x_two_third - x_third) * 0.86602540378 + y_third + (y_two_third - y_third) * 0.5;

        // Recursive calls for the four sub-segments
        draw_koch_curve(x1, y1, x_third, y_third, depth - 1);
        draw_koch_curve(x_third, y_third, peak_x, peak_y, depth - 1);
        draw_koch_curve(peak_x, peak_y, x_two_third, y_two_third, depth - 1);
        draw_koch_curve(x_two_third, y_two_third, x2, y2, depth - 1);
    }
}

int main(void) {
    // Start the Koch curve from (0,0) to (100,0) with a recursion depth of 3
    draw_koch_curve(0.0, 0.0, 100.0, 0.0, 3);
    return 0;
}
