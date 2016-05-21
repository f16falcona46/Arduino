//#include <avr/interrupt.h>
//#include <avr/io.h>
//#define F_CPU 16000000UL // 16 MHz
//#include <util/delay.h>
#include <stdlib.h>
#include "Servo.h"

void setup() {
	Servo servos[6];
	Serial.begin(115000);
	Serial.println("lol");
	int servo_commands[6];
	
	servos[0].attach(8); //elevator base
	servos[1].attach(9); //rotator base
	servos[2].attach(10); //elevator elbow
	servos[3].attach(11); //elevator wrist
	servos[4].attach(12);//claw
	
	while(1) {
		int reading = analogRead(0);
		servos[0].writeMicroseconds(map(reading, 0, 1023, 4000, 500));
		
		reading = analogRead(1);
		servos[1].writeMicroseconds(map(reading, 0, 1023, 4000, 1500));
		
		reading = analogRead(2);
		servos[2].writeMicroseconds(map(reading, 0, 1023, 4000, 250));
		
		reading = analogRead(3);
		servos[3].writeMicroseconds(map(reading, 0, 1023, 500, 4000));
		
		reading = analogRead(4);
		servos[4].writeMicroseconds(map(reading, 0, 1023, 4000, 500));
		
		delay(100);
	}
}

void loop() {}