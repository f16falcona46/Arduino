/*
	NAME:
	ATMega Control Program for Robot Arm
	
	DESCRIPTION:
	Controls servos attached to the robot arm using potentiometers with
		a range of 0V to 5V.
	
	(C) 2016 Jason Li
	
	COMPATIBILITY:
	Used on Arduino Nano or clones, or ATMega168/328(P).
	Only needs 5 or 6 ADCs, so will work with DIP version.

	PINOUT:
		D2, A0: Main Rotator
		D3, A1: Main Elevator
		D4, A2: Elbow
		D5, A3: Wrist
		D6, A4: Left Finger
		D7, (A5): Right Finger (Control knob optional. Can be computed)
	
	NOTES:
	To compute D5 servo instead of using a potentiometer, define the
		macro "COMPUTED_SERVO"; however, it is not tested yet.
	If using potentiometers of resistance of around 1MOhm, it's best
		to use a bypass capacitor, for example, a ceramic 0.01uF one.
		Even 100KOhm may need one. This capacitor reduces noise and
		therefore preserves the motors.
	Nano servos can't take more than 9v, or else they will burn. High
		torque servos can take up to 12v.
*/

#include <Servo.h>

#define NUM_SERVOS 6

#ifdef COMPUTED_SERVO
#define NUM_POTS 5
#else
#define NUM_POTS 6
#endif

int main() {
	init();
	Servo servos[NUM_SERVOS];
	for (int i = 0; i < NUM_SERVOS; ++i) {
		servos[i].attach(i+2);
	}
	while(1) {
		for (int i = 0; i < NUM_POTS; ++i) {
			servos[i].writeMicroseconds(500+2*analogRead(i));
		}
		#ifdef COMPUTED_SERVO
		servos[NUM_SERVOS-1].writeMicroseconds(2500-2*analogRead(NUM_POTS-1));
		#endif
		delay(10);
	}
}
