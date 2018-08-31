#include <reg51.h>
void main(void) {
	for(;;) {
		P1 = 0xFF;
		P1 = 0x00;
	}
}
