#include <util/delay_basic.h>
	
	/*

//flash B5 (Digital 13) LED
int main() {
	init();
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	//DDRB |= (1<<PB5);
	analogWrite(0, 200);
	analogWrite(1, 200);
	while (1) {
	}
}
*/
//11 right
//10 left
void setup() {
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	analogWrite(10, 160);
	analogWrite(11, 255);
}

void loop() {
}