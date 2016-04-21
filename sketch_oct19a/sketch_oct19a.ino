#include <avr/interrupt.h>
#include <avr/io.h>

unsigned static volatile int left_count;
unsigned static volatile int right_count;

ISR(INT0_vect) {
	++left_count;
}

ISR(INT1_vect) {
	++right_count;
}

int main() {
	DDRD = DDRD & ~(1<<2 | 1<<3);
	
	EIMSK |= 1<<INT0;
	EIMSK |= 1<<INT1;
	
	EICRA |= 1<<ISC11;
	EICRA |= 1<<ISC01;
	sei();
	
	while(1);
	//               ROM RAM
	//Arduino style: 570 13
	//Traditional C: 274 4
}
