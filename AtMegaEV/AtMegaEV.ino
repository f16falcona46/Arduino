#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 16000000UL // 16 MHz
#include <util/delay.h>

unsigned static volatile int left_count;
unsigned static volatile int left_count_large;

ISR(INT0_vect) {
	++left_count;
	PORTB^=(1<<PB5);
}

int main() {
	constexpr int dist_large = 0;
	constexpr int dist = 400; //NOTE: Add about 25cm to the given distance to get the final distance!
	DDRD = DDRD & ~(1<<2 | 1<<3);
	DDRB|=(1<<PB5);
	DDRD|=(1<<PD5);
	
	EIMSK |= 1<<INT0;
	
	EICRA |= 1<<ISC00; //Not sure if this is for INT1 or INT0, but I think it is INT1
	while (PORTD&(1<<PD6)); //set 300 got 274
	sei();
	
	PORTB ^=(1<<PB5);
	_delay_ms(1000);
	
	PORTD |= (1<<PD5);
	while (left_count_large < dist_large) {
		while (left_count < 65535);
		left_count = 0;
		++left_count_large;
	}
	left_count = 0;
	while (left_count < dist);
	PORTD &= ~(1<<PD5);
}
