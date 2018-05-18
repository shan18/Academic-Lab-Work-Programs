#include <graphics.h>


int abs(int n) {
	return ((n > 0) ? n: (n * -1));
}

void dda(int x0, int y0, int x1, int y1) {
	int dx = x1 - x0;
	int dy = y1 - y0;

	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	int xi = dx / (float) steps;
	int yi = dy / (float) steps;

	float x = x0;
	float y = y0;
	for(int i=1; i <= steps; i++) {
		putpixel(x, y, WHITE);
		x += xi;
		y += yi;
		delay(80);
	}
}

int main() {
	int gd = DETECT, gm;
	initgraph (&gd, &gm, "");
	dda(50, 150, 250, 250);

	delay(2000);
   	closegraph();

	return 0;
}
