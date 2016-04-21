//#include <avr/interrupt.h>
//#include <avr/io.h>
//#define F_CPU 16000000UL // 16 MHz
//#include <util/delay.h>
#include <stdlib.h>
#include "Servo.h"

void setup() {
	Servo servos[6];
	Serial.begin(115000);
	int servo_commands[6];
	
	servos[0].attach(6); //rotator base
	servos[1].attach(7); //elevator base
	servos[2].attach(8); //elevator elbow
	servos[3].attach(9); //elevator wrist
	servos[4].attach(10);//rotator right finger
	servos[5].attach(11);//rotator left finger
	
	while(1) {
		servos[rand()%6].writeMicroseconds(rand()%1100+1000);
		delay(100);
		/*
		if (Serial.available() >= 13) {
			char in = Serial.read();
			if (in == 255) {
				for (int i = 0; i < 6; ++i) {
					char high = Serial.read();
					char low = Serial.read();
					servos[i].writeMicroseconds(256*high+low);
				}
			}
		}
		*/
		
	}
}

void loop() {}