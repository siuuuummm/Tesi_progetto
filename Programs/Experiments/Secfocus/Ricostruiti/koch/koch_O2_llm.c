#include <stdio.h>
#include <math.h>

/**
 * The binary implements the Koch Curve fractal.
 * It recursively divides a line segment into four parts, 
 * creating a "spike" in the middle.
 */

void koch_curve(double x1, double y1, double x2, double y2, int depth) {
    if (depth == 0) {
        printf("Linea da (%f,%f) a (%f,%f)\n", x1, y1, x2, y2);
        return;
    }

    // Calculate distance components
    double dx = x2 - x1;
    double dy = y2 - y1;

    // Dividing the line into 3 equal parts
    // mid1 = (x1 + dx/3, y1 + dy/3)
    // mid3 = (x1 + 2*dx/3, y1 + 2*dy/3)
    double mid1_x = x1 + dx / 3.0;
    double mid1_y = y1 + dy / 3.0;
    double mid3_x = x1 + 2.0 * dx / 3.0;
    double mid3_y = y1 + 2.0 * dy / 3.0;

    // Calculate the peak of the triangle (rotate vector mid1->mid3 by 60 degrees)
    // cos(60°) = 0.5, sin(60°) = sqrt(3)/2 ≈ 0.86602540378
    double cos60 = 0.5;
    double sin60 = 0.86602540378;
    
    double segment_dx = dx / 3.0;
    double segment_dy = dy / 3.0;

    double peak_x = (segment_dx * cos60 + mid1_x) - (segment_dy * sin60);
    double peak_y = (segment_dx * sin60 + mid1_y) + (segment_dy * cos60);

    // Recursive calls for the 4 segments
    koch_curve(x1, y1, mid1_x, mid1_y, depth - 1);
    koch_curve(mid1_x, mid1_y, peak_x, peak_y, depth - 1);
    koch_curve(peak_x, peak_y, mid3_x, mid3_y, depth - 1);
    koch_curve(mid3_x, mid3_y, x2, y2, depth - 1);
}

int main(void) {
    // Based on the binary: 
    // x1=0, y1=0, x2=100.0, y2=0, depth=3
    koch_curve(0.0, 0.0, 100.0, 0.0, 3);
    return 0;
}
