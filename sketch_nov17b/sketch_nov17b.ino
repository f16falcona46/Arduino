#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 16000000UL // 16 MHz
#include <util/delay.h>

unsigned static volatile int left_count;
unsigned static volatile int right_count;

ISR(INT0_vect) {
	++left_count;
}

ISR(INT1_vect) {
	++right_count;
}

int main() {	
	DDRB = 255;
	DDRD = DDRD & ~(1<<2 | 1<<3);
	
	EIMSK |= 1<<INT0;
	EIMSK |= 1<<INT1;
	
	EICRA |= 1<<ISC11;
	EICRA |= 1<<ISC01;
	sei();
	
		//Configure TIMER1
	TCCR1A|=(1<<COM1A1)|(1<<WGM11);		  //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)

	ICR1=4999;  //fPWM=50Hz (Period = 20ms Standard).

	DDRD|=(1<<PD4)|(1<<PD5);	//PWM Pins as Out

	while(1) {
		for (int i = 13824; i < 33600; i+=300) {
			OCR1A=i;
			_delay_ms(100);
		}
	}	
	//					ROM RAM
	//Arduino style: 570 13
	//Traditional C: 274 4
}
