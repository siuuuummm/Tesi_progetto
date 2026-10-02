#include <stdio.h>
#include <math.h>

/**
 * Recursive function to draw a Koch curve.
 * @param x1 Starting X coordinate
 * @param y1 Starting Y coordinate
 * @param x2 Ending X coordinate
 * @param y2 Ending Y coordinate
 * @param depth Recursion depth
 */
void draw_koch(double x1, double y1, double x2, double y2, int depth) {
    if (depth == 0) {
        // Base case: print the line segment
        printf("Linea da (%f,%f) a (%f,%f)\n", x1, y1, x2, y2);
    } else {
        // Divide the line into three equal parts
        double x_mid1 = x1 + (x2 - x1) / 3.0;
        double y_mid1 = y1 + (y2 - y1) / 3.0;
        double x_mid2 = x1 + 2.0 * (x2 - x1) / 3.0;
        double y_mid2 = y1 + 2.0 * (y2 - y1) / 3.0;

        // The angle for the peak of the Koch curve is 60 degrees (PI/3 radians)
        double angle = M_PI / 3.0;
        double cos_a = cos(angle);
        double sin_a = sin(angle);

        // Calculate the peak point of the equilateral triangle
        // Rotation of the vector (x_mid2 - x_mid1, y_mid2 - y_mid1) by 60 degrees
        double x_peak = cos_a * (x_mid2 - x_mid1) - sin_a * (y_mid2 - y_mid1) + x_mid1;
        double y_peak = sin_a * (x_mid2 - x_mid1) + cos_a * (y_mid2 - y_mid1) + y_mid1;

        // Recursive calls for the four segments of the Koch curve
        draw_koch(x1, y1, x_mid1, y_mid1, depth - 1);
        draw_koch(x_mid1, y_mid1, x_peak, y_peak, depth - 1);
        draw_koch(x_peak, y_peak, x_mid2, y_mid2, depth - 1);
        draw_koch(x_mid2, y_mid2, x2, y2, depth - 1);
    }
}

int main(void) {
    // The original binary calls the function with (0, 0, 100, 0, 3)
    draw_koch(0.0, 0.0, 100.0, 0.0, 3);
    return 0;
}
