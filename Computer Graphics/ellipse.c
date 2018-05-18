#include <stdio.h>
#include <graphics.h>


void plot_ellipse(int xc, int yc, int x, int y) {
    putpixel(xc + x, yc + y, WHITE);
    putpixel(xc - x, yc + y, WHITE);
    putpixel(xc + x, yc - y, WHITE);
    putpixel(xc - x, yc - y, WHITE);
}

void draw_ellipse(long xc, long yc, long xr, long yr) {
    long xr_sq = xr * xr;
    long yr_sq = yr * yr;

    long two_xr_sq = 2 * xr_sq;
    long two_yr_sq = 2 * yr_sq;

    long x = 0, dpx = 0;  // decision parameter for x
    long y = yr;
    long dpy = two_xr_sq * y;  // decision parameter for y

    plot_ellipse(xc, yc, x, y);

    // Descision Parameter
    long dp = (long) (yr_sq - (xr_sq * yr) + (0.25 * xr_sq));

    while(dpx < dpy) {
        x++;
        dpx += two_yr_sq;
        if(dp < 0)
            dp += yr_sq + dpx;
        else {
            y--;
            dpy -= two_xr_sq;
            dp += yr_sq + dpx - dpy;
        }
        plot_ellipse(xc, yc, x, y); // plot points in y-axis (top/bottom)
        delay(100);
    }

    dp = (long)(
        yr_sq * (x + 0.5) * (x + 0.5) + xr_sq * (y - 1) * (y - 1) - xr_sq * yr_sq
    );

    while(y > 0) {
        y--;
        dpy = dpy - two_xr_sq;
        if(dp > 0)
            dp += xr_sq - dpy;
        else {
            x++;
            dpx += two_yr_sq;
            dp += xr_sq - dpy + dpx;
        }

        plot_ellipse(xc, yc, x, y); // plot points in x-axis (left/right)
    }
    delay(500);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    long xc = getmaxx() / 2;  // center x-coordinate
    long yc = getmaxy() / 2;  // center y-coordinate
    draw_ellipse(xc, yc, 100, 50);

    delay(2000);
    closegraph();
}
