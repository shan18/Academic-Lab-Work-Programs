/* Rotaion of a triangle
 * In Linux, run this program with the following command:
 * gcc -o triangle_rotation triangle_rotation.c -lgraph -lm
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <graphics.h>


void rotation(double x[], double y[], double ref[], double angle) {
    for(int i=0; i < 3; i++) {
        x[i] = ref[0] + (x[i] - ref[0]) * cos(angle) - (y[i] - ref[1]) * sin(angle);
        y[i] = ref[1] + (x[i] - ref[0]) * sin(angle) + (y[i] - ref[1]) * cos(angle);
    }
}

void rotate_triangle(double x[], double y[], double ref[], double angle) {
    // Draw original square
    setcolor(1);
    line(x[0], y[0], x[1], y[1]);
    line(x[1], y[1], x[2], y[2]);
    line(x[2], y[2], x[0], y[0]);

    angle = angle * (3.14 / 180);  // convert angle to radians
    rotation(x, y, ref, angle);

    // Draw scaled square
    setcolor(2);
    line(x[0], y[0], x[1], y[1]);
    line(x[1], y[1], x[2], y[2]);
    line(x[2], y[2], x[0], y[0]);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    double x[] = {100, 150, 200};  // x-coordinates
    double y[] = {100, 150, 100};  // y-coordinates
    double ref[] = {100, 100};  // rotation about this point
    double angle = 30;  // In degrees
    
    rotate_triangle(x, y, ref, angle);

    delay(3000);
    closegraph();
    return 0;
}
