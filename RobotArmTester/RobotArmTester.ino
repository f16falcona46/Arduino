/*
	NAME:
	ATMega Tester Program for Robot Arm
	
	DESCRIPTION:
	Used to find the initial values for driving the servos.
	
	(C) 2016 Jason Li
	
	COMPATIBILITY:
	Used on Arduino Nano or clones, or ATMega168/328(P).
	
	PINOUT:
		A0: 0-5V signal representing the angle
		D13: Servo pulse output
*/

#include <Servo.h>

int main() {
	init();
	Serial.begin(9600);
	Servo s1 = Servo();
	s1.attach(13);
	
	while(1) {
		s1.writeMicroseconds(500+2*analogRead(0));
		Serial.println(500+2*analogRead(0));
		delay(15);
	}
}
