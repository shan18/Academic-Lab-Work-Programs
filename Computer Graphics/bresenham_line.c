#include <stdio.h>
#include <graphics.h>


void bresenham(int x0, int y0, int x1, int y1) {
    putpixel(x0, y0, WHITE);  // Initial point
    putpixel(x1, y1, WHITE);  // Final point

    int dx = (x1 - x0);
    int dy = (y1 - y0);

    int pk_temp = 2 * dy;
    int pk = pk_temp - dx;  // P0 = 2 * dy - dx

    for(int x=x0, y=y0; x <= x1; x++) {
        putpixel(x, y, GREEN);
        pk = pk + pk_temp;  // Pk = P0 + 2 * dy
        if(pk >= 0) {
            y++;
            pk = pk - 2 * dx;  // pk+1 = pk +  2dy - 2dx
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    bresenham(2, 2, 100, 55);

    delay(2000);
    closegraph();
}
