/**************************************************************************************

This is example for ClosedCube TSYS01 +/-0.1C 24-bit ADC Temperature Sensor Breakout

Initial Date: 27-Jul-2017

Hardware connections for Arduino Uno:
VDD to 3.3V DC
SCL to A5
SDA to A4
GND to common ground

Written by AA for ClosedCube

MIT License

**************************************************************************************/

#include "ClosedCube_TSYS01.h"

ClosedCube_TSYS01 tsys01;

void setup()
{
	Serial.begin(9600);
	Serial.println("ClosedCube TSYS01 Arduino Test");

	tsys01.begin(0x77);
}

void loop()
{
	Serial.print("T=");
	Serial.print(tsys01.readTemperature());
	Serial.println("C");
	delay(100);
}
