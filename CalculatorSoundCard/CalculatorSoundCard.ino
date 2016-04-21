/*
	NAME:
	Sound Card for HP 49G
	
	DESCRIPTION:
	Based on commands from the HP 49G's serial port, stores and plays
		tones (up to four at a time).
	
	(C) 2016 Rusty Nail
	
	COMPATIBILITY:
	Used on Arduino Nano or clones, or ATMega168/328(P).

	PINOUT:
		B1: Speaker (Piezo)
		D0: Rx from calculator
		D1: Tx to calculator, unusued
	
	NOTES:
	Recommended to put a 68 ohm resistor in series with speaker pin, and
		a 0.1 uF capacitor in parallel with the speaker. This smooths out
		the PWM output.
*/

#include <util/delay.h>
#define F_CPU 16000000
/*
No newlines!
"S090035"
Start, 090 BPM, 035 notes
"AX5005B+4067"
channel 1
A5 natural for 5 beats
B4 sharp for 67 beats
...
"C" (next channel)
...
...
"N" (End)
*/

/*
	Cb	0
	C	1
	C#	2
	D	3
	D#	4
	E	5
	F	6
	F#	7
	G	8
	G#	9
	A	10
	A#	11
	B	12
	B#	13
*/

constexpr int PROGMEM note_lookup[] = {
	10,//A
	12,//B
	1, //C
	3, //D
	5, //E
	6, //F
	8, //G
}

constexpr int PROGMEM note_lengths[] = {
	
}

int main() {
	init();
	Serial.begin(9600);
	DDRB |= (1<<PB1);
	
	while (1) {
		if (Serial.available()) {
			int c = Serial.read();
			if (c>='A' && c<='G') {
				int sharp_or_flat = Serial.read();
				int octave = Serial.read()-'0';
				int length_hundreds_digit = Serial.read();
				int length_tens_digit = Serial.read();
				int length_ones_digit = Serial.read();
				int length = length_hundreds_digit*100 + length_tens_digit*10 + length_ones_digit;
				
			}
		}
	}
}
