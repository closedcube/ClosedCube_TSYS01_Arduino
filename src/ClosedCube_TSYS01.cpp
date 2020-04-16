/*

Arduino library for Arduino library for TE CONNECTIVITY +/-0.1C 24-bit Digital Temperature Sensor
version 2020.4.16

---

Copyright (c) 2018-2020, ClosedCube
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation and/or 
   other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors 
   may be used to endorse or promote products derived from this software
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "ClosedCube_TSYS01.h"

ClosedCube::Sensor::TSYS01::TSYS01() {
	_i2c.init();
}

void ClosedCube::Sensor::TSYS01::begin(uint8_t address) {
	_i2c.address(address);

	_k4 = readPROM(0xA2);
	_k3 = readPROM(0xA4);
	_k2 = readPROM(0xA6);
	_k1 = readPROM(0xA8);
	_k0 = readPROM(0xAA);
}

float ClosedCube::Sensor::TSYS01::readTemperature() {
	float result = 0;

	_i2c.writeByte(0x48);

	delay(15);

	uint16_t adc16 = readADC24()/256;

	result = (-2.0)*_k4*pow(10, -21)*pow(adc16, 4) +
		4.0 *_k3*pow(10, -16)*pow(adc16, 3) +
		(-2.0)*_k2*pow(10, -11)*pow(adc16, 2) +
		1.0*_k1*pow(10, -6)*adc16 +
		(-1.5)*_k0*pow(10,-2);
	
	return result;
}

float ClosedCube::Sensor::TSYS01::readT() {
	return readTemperature();
}

uint32_t ClosedCube::Sensor::TSYS01::readADC24() {
	_i2c.writeByte(0x00);

	delay(5);

	byte buf[3];
	_i2c.readBytes(buf,3);

	return buf[0]*pow(2,16) + buf[1]*pow(2,8) + buf[0];
}

uint16_t ClosedCube::Sensor::TSYS01::readPROM(uint8_t calibration) {
	_i2c.writeByte(calibration);
	delay(5);
	return _i2c.readWord();
}
