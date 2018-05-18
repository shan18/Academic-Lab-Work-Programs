#include <stdio.h>
#include <graphics.h>


void find_new_coordinate(int s[][2], int p[][1]) {
    p[0][0] = s[0][0] * p[0][0];
    p[1][0] = s[1][1] * p[1][0];
}

void scale_square(int x[], int y[], int sx, int sy) {
    // Draw original square
    line(x[0], y[0], x[1], y[1]);
    line(x[1], y[1], x[2], y[2]);
    line(x[2], y[2], x[3], y[3]);
    line(x[3], y[3], x[0], y[0]);

    // Initialize the scaling matrix
    int s[2][2] = {sx, 0, 0, sy};
    int p[2][1];

    // perform scaling
    for(int i=0; i < 4; i++) {
        p[0][0] = x[i];
        p[1][0] = y[i];

        find_new_coordinate(s, p);

        x[i] = p[0][0];
        y[i] = p[1][0];
    }

    // Draw scaled square
    line(x[0], y[0], x[1], y[1]);
    line(x[1], y[1], x[2], y[2]);
    line(x[2], y[2], x[3], y[3]);
    line(x[3], y[3], x[0], y[0]);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int x[] = {0, 40, 40, 0};  // x-coordinates
    int y[] = {0, 0, 40, 40};  // y-coordinates
    int sx = 2, sy = 2;  // scaling factor
    
    scale_square(x, y, sx, sy);

    delay(3000);
    closegraph();
    return 0;
}
