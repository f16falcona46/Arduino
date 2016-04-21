/*
	NAME:
	ATTiny Control Program for Electric Vehicle
	
	DESCRIPTION:
	Waits for press of start button, then enables motor and counts pulses from encoder
		wheel. Ends when the number of pulses meets a predefined value, and then
		enables the brakes. All buttons are active low, while the motors are connected
		to MOSFETS that are active high.
	
	(C) 2016 Jason Li
	
	COMPATIBILITY:
	Used on ATTiny 25/45/85 series.
	
	PINOUT:
		PB0: Encoder
		PB1: Activation switch
		PB2: Indicator LED
		PB3: Motor on MOSFET
		PB4: Motor brake MOSFET
*/

#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 8000000UL // 8 MHz
#include <util/delay.h>

unsigned static volatile int left_count = 0;
unsigned static volatile int left_count_large = 0;

constexpr int dist_large = 0; //total distance = 65535*dist_large+dist
constexpr int dist = 1242;

//n=-100/553*(math.sqrt(219654068-138250*d)-15500)
//d in centimeters

ISR(PCINT0_vect) {
	++left_count;
	PORTB^=(1<<PB2); //blink indicator LED
}

//N=1.622L-290.83, L in cm

//800 22'0.5" 671.83cm
//1000 27'6.5" 2'5" 839.47cm
//1200 28'2" 2' 858.52cm
//1400 34'0" 1036.32cm
//1600 39'0.5" 1189.99cm

int main() {
	
	DDRB = DDRB|(1<<PB2)|(1<<PB3)|(1<<PB4); //enable outputs on LED and MOSFET outputs
	
	PORTB = (1<<PB1)|(1<<PB4); //set pullup on switch, enable brake
	
	GIMSK |= (1<<PCIE); //enable pin change interrupt
	PCMSK |= (1<<PCINT0); //pin change interrupt on pin 0
	
	sei();
	
	while (PINB&(1<<PB1)); //wait until button pressed
	_delay_ms(500);
	PORTB &= ~(1<<PB4); //brake off
	_delay_ms(500);
	PORTB |= (1<<PB3); //motor on
	
	while (left_count_large < dist_large) {
		while (left_count < 65535);
		left_count = 0;
		++left_count_large;
	}
	left_count = 0;
	while (left_count < dist);
	PORTB &= ~(1<<PB3); //stop motor
	PORTB = (1<<PB4); //brake
}
