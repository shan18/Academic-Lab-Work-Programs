#include <stdio.h>
#include <math.h>
#include <graphics.h>


void plot_circle(int xc, int yc, int x, int y) {
    // Reflection about y axis and x axis
    putpixel(xc+x, yc+y, WHITE);
    putpixel(xc+x, yc-y, WHITE);
    putpixel(xc-x, yc+y, WHITE);
    putpixel(xc-x, yc-y, WHITE);
    // Reflection about line y=x
    putpixel(xc+y, yc+x, WHITE);
    putpixel(xc-y, yc+x, WHITE);
    putpixel(xc+y, yc-x, WHITE);
    putpixel(xc-y, yc-x, WHITE);
}

void circle(int xc, int yc, int r) {
    // starting from (0, r)
    int p = 5 / 4 - r;    // decision parameter
    int x = 0;
    int y = r;

    while(x <= y) {
        if(p < 0) {
            p += 2 * x + 3;
            x++;
        } else {
            p += 2 * (x - y) + 5;
            x++;
            y--;
        }
        plot_circle(xc, yc, x, y);
        delay(100);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    circle(250, 250, 50);

    delay(2000);
    closegraph();
}
