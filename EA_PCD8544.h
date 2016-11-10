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

#ifndef __EA_PCD8544_h
#define __EA_PCD8544_h

#include "config.h"
#include "utils.h"
#include "draw.h"
#include "draw_fonts.h"
#include "ea_bitmaps.h"

#define		DISPLAY_WIDTH	84
#define		DISPLAY_HEIGHT	48

#define		FUNCTION_SET_BYTE		0x20
#define		DISPLAY_CTRL_BYTE		0x08
#define		Y_ADDR_RAM_BYTE			0x40
#define		X_ADDR_RAM_BYTE			0x80
#define		TEMP_CTRL_BYTE			0x04
#define		BIAS_SYSTEM_BYTE		0x10
#define		SET_VOP_BYTE			0x80

#define		DISPLAY_BLANK			0x00
#define		DISPLAY_NORMAL			0x04
#define		DISPLAY_ALL_ON			0x01
#define		DISPLAY_INVERT			0x05

#define		BIT_PD	2
#define		BIT_V	1
#define		BIT_H	0

class PCD8544 {
private:
	uns8	_dataPin;
	uns8	_clkPin;
	uns8	_cePin;
	uns8	_dcPin;
	uns8	_rstPin;
	uns8	_addressingMode;
	uns8	configurationByte;
	
	inline void		_command(uns8 cmd);
	
	
public:
	PCD8544(uns8 data, uns8 clk, uns8 rst, uns8 ce, uns8 dc);
	
	void	begin();
	void	enableVerticalAddressing(bool en = true);
	void	enableExtendedInstructions(bool en = true);
	void	enablePowerDown(bool en = true);
	void	setConfiguration();
	void	setTemperatureControl(uns8 temp);
	void	setBiasSystem(uns8 bias);
	void	setDisplayMode(uns8 mode);
	void	setContrast(uns8 vop);
	void	writeRAM(uns8 *buffer);
	void	setRamXAddress(uns8 xaddr);
	void	setRamYAddress(uns8 yaddr);
	
};

#endif