#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

int main() {
	DDRB |= (1<<PB3);
	while (1) {
		PORTB ^= (1<<PB3);
		_delay_ms(500);
	}
}