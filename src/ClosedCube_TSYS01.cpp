/*

Arduino library for TE CONNECTIVITY TSYS01 +/-0.1C 24-bit Digital Temperature Sensor
Written by AA for ClosedCube
---

The MIT License (MIT)

Copyright (c) 2017 ClosedCube Limited

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include <Wire.h>
#include "ClosedCube_TSYS01.h"

ClosedCube_TSYS01::ClosedCube_TSYS01()
{
}

void ClosedCube_TSYS01::begin(uint8_t address) {
	_address = address;
	Wire.begin();

	_k4 = readPROM(0xA2);
	_k3 = readPROM(0xA4);
	_k2 = readPROM(0xA6);
	_k1 = readPROM(0xA8);
	_k0 = readPROM(0xAA);
}

float ClosedCube_TSYS01::readTemperature() {
	float result = 0;

	Wire.beginTransmission(_address);
	Wire.write(0x48);
	Wire.endTransmission(true);

	delay(15);

	float adc16 = readADC24()/256.0;

	result = (-2.0)*_k4*pow(10, -21)*pow(adc16, 4) +
		4.0 *_k3*pow(10, -16)*pow(adc16, 3) +
		(-2.0)*_k2*pow(10, -11)*pow(adc16, 2) +
		1.0*_k1*pow(10, -6)*adc16 +
		(-1.5)*_k0*pow(10,-2);
	
	return result;
}

float ClosedCube_TSYS01::readT() {
	return readTemperature();
}

uint32_t ClosedCube_TSYS01::readADC24() {
	Wire.beginTransmission(_address);
	Wire.write(0x00);
	Wire.endTransmission();

	delay(5);
	Wire.requestFrom(_address, (uint8_t)3);

	byte buf[3];
	Wire.readBytes(buf, 3);

	return buf[0]*pow(2,16) + buf[1]*pow(2,8) + buf[0];
}

uint16_t ClosedCube_TSYS01::readPROM(uint8_t calibration) {
	Wire.beginTransmission(_address);
	Wire.write(calibration);
	Wire.endTransmission();

	delay(5);

	Wire.requestFrom(_address, (uint8_t)2);

	byte msb = Wire.read();
	byte lsb = Wire.read();

	return msb << 8 | lsb;
}
