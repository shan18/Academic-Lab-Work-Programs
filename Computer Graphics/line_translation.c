#include <stdio.h>
#include <graphics.h>


void translate_line(int line_points[][2], int trans_factor[]) {
    // draw original line
    setcolor(2);
    line(line_points[0][0], line_points[0][1], line_points[1][0], line_points[1][1]);

    // calculate translated coordinates
    line_points[0][0] = line_points[0][0] + trans_factor[0];
    line_points[0][1] = line_points[0][1] + trans_factor[1];
    line_points[1][0] = line_points[1][0] + trans_factor[0];
    line_points[1][1] = line_points[1][1] + trans_factor[1];

    // draw translated line
    setcolor(3);
    line(line_points[0][0], line_points[0][1], line_points[1][0], line_points[1][1]);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int line_points[][2] = {20, 20, 120, 20};  // x1, y1, x2, y2
    int trans_factor[] = {0, 100};
    translate_line(line_points, trans_factor);

    delay(3000);
    closegraph();
    return 0;
}
