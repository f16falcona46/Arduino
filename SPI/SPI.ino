#include <avr/interrupt.h>
#include <avr/io.h>
#include <SPI.h>

int main() {
	init();
	Serial.begin(9600);
	SPI.begin();
	for (unsigned char i = 0; i < 255; ++i) {
		Serial.print("i:");
		Serial.print(i);
		unsigned char j=SPI.transfer(i)+1;
		Serial.print(" ");
		Serial.println(j);
	}
	while(1);
}
