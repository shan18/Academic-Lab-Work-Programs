#include <reg51.h>
sbit LED = P1^0;
void delay(void);
void main(void) {
	while(1) {
		LED = 0;
		delay();
		LED=1;
		delay();
	}
}

void delay() {
	int i, j;
	for(i=0; i<=100; i++) {
		for(j=0; j<=100; j++) {
		}
	}
}

