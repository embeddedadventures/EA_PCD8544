/*
Copyright (c) 2016, Embedded Adventures, www.embeddedadventures.com
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
- Neither the name of Embedded Adventures nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
THE POSSIBILITY OF SUCH DAMAGE.
Contact us at admin [at] embeddedadventures.com

*/

#include "EA_PCD8544.h"

//#define PCD8544_DEBUG
#ifdef	PCD8544_DEBUG
	#define DEBUGLN(x)	Serial.println(x);
	#define	DEBUGX(x)	Serial.println(x, HEX);
	#define	DEBUG(x)	Serial.print(x);
#else
	#define DEBUGLN(x)	
	#define	DEBUGX(x)	
	#define	DEBUG(x)	
#endif

PCD8544::PCD8544(uns8 data, uns8 clk, uns8 rst, uns8 ce, uns8 dc) {
	_dataPin = data;
	_clkPin = clk;
	_rstPin = rst;
	_cePin = ce;
	_dcPin = dc;
	pinMode(_rstPin, OUTPUT);
	digitalWrite(_rstPin, HIGH);
	pinMode(_dcPin, OUTPUT);
	pinMode(_cePin, OUTPUT);
	digitalWrite(_cePin, HIGH);
	pinMode(_dataPin, OUTPUT);
	pinMode(_clkPin, OUTPUT);
}

void PCD8544::_command(uns8 cmd) {
	DEBUGX(cmd);
	digitalWrite(_dcPin, LOW);
	digitalWrite(_cePin, LOW);
	shiftOut(_dataPin, _clkPin, MSBFIRST, cmd);
	digitalWrite(_cePin, HIGH);
}

void PCD8544::begin() {
	configurationByte = FUNCTION_SET_BYTE;
	DEBUGLN("in begin");
	digitalWrite(_rstPin, LOW);
	delay(1);
	digitalWrite(_rstPin, HIGH);
	DEBUGLN("after rst");
	enableVerticalAddressing();
	enableExtendedInstructions();
	setContrast(0x4F);
	setTemperatureControl(0);
	setBiasSystem(4);
	enableExtendedInstructions(false);
	setDisplayMode(DISPLAY_NORMAL);
	setRamXAddress(0);
	setRamYAddress(0);	
	DEBUGLN("exit begin");
	
}

void PCD8544::enableVerticalAddressing(bool en) {
	DEBUG("enableVerticalAddressing: ");
	//uns8 configurationByte = FUNCTION_SET_BYTE;
	if (en) {
		bitSet(configurationByte, BIT_V);
		_addressingMode = 1;
	}
	else {
		bitClear(configurationByte, BIT_V);
		_addressingMode = 0;
	}
}

void PCD8544::enableExtendedInstructions(bool en) {
	//uns8 configurationByte = FUNCTION_SET_BYTE;
	if (en) {
		bitSet(configurationByte, BIT_H);
	}
	else {
		bitClear(configurationByte, BIT_H);
	}
	DEBUG("enableExtendedInstructions: ");
	_command(configurationByte);
}

void PCD8544::enablePowerDown(bool en) {
	DEBUG("enablePowerDown: ");
	//uns8 configurationByte = FUNCTION_SET_BYTE;
	if (en) {
		bitSet(configurationByte, BIT_PD);
	}
	else {
		bitClear(configurationByte, BIT_PD);
	}
	_command(configurationByte);
}

void PCD8544::setDisplayMode(uns8 mode) {
	DEBUG("setDisplayMode: ");
	_command(DISPLAY_CTRL_BYTE | mode);
}

void PCD8544::setTemperatureControl(uns8 temp) {
	DEBUG("setTemperatureControl: ");
	temp &= 0x03;
	_command(temp | TEMP_CTRL_BYTE);
}

void PCD8544::setBiasSystem(uns8 bias) {
	DEBUG("setBiasSystem: ");
	bias &= 0x03;
	_command(bias | BIAS_SYSTEM_BYTE);
	
}

void PCD8544::setContrast(uns8 vop) {
	DEBUG("setContrast: ");
	_command(vop | SET_VOP_BYTE);
}

void PCD8544::writeRAM(uns8 *buffer) {
	DEBUGLN("writeRAM: ");
	for (int i = 0; i < DISPLAY_HEIGHT * DISPLAY_WIDTH / 8; i++) {
		digitalWrite(_dcPin, HIGH);
		digitalWrite(_cePin, LOW);
		shiftOut(_dataPin, _clkPin, MSBFIRST, buffer[i]);
		digitalWrite(_cePin, HIGH);
	}
}

void PCD8544::setRamXAddress(uns8 xaddr) {
	DEBUG("setRamXAddress: ");
	if (xaddr > 53)
		xaddr = 53;
	_command(xaddr | X_ADDR_RAM_BYTE);
}

void PCD8544::setRamYAddress(uns8 yaddr) {
	DEBUG("setRamYAddress: ");
	if (yaddr > 5) 
		yaddr = 5;
	_command(yaddr | Y_ADDR_RAM_BYTE);
}

