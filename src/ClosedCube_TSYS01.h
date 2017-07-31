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

#ifndef _CLOSEDCUBE_TSYS01_h
#define _CLOSEDCUBE_TSYS01_h

#include <Arduino.h>

class ClosedCube_TSYS01 {
public:
	ClosedCube_TSYS01();

	void begin(uint8_t address);

	float readTemperature();
	float readT(); // short-cut for readTemperature

private:
	uint8_t _address;
	uint16_t _k0, _k1, _k2, _k3, _k4;
	uint16_t readPROM(uint8_t calibration);
	uint32_t readADC24();
};


#endif

