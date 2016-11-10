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

#include <draw.h>
#include <EA_PCD8544.h>

const uns8 dataPin = 13;
const uns8 clkPin = 14;
const uns8 dcPin = 12;
const uns8 cePin = 2;
const uns8 rstPin = 15;

PCD8544 nokia(dataPin, clkPin, rstPin, cePin, dcPin);

void setup() {
  Serial.begin(115200);
  Serial.println("Welcome to the Embedded Adventures LCD-8448GR demo sketch");
  Serial.println("(www.embeddedadventures.com)");
  nokia.begin();
  draw_init(DISPLAY_WIDTH, DISPLAY_HEIGHT, 1);
  draw_fonts_init();
  logo(8, 0);
}

void loop() {

}

void drv_paint() {
  nokia.writeRAM(draw_buffer);
}

void logo(uns16 x, uns16 y) {
  draw_clear_screen();
  delay(100);
  draw_bitmap(x, y, 1, e_big_bitmap);
  draw_bitmap(x+33, y, 1, a_big_bitmap);
  draw_fonts_print_str(DRAW_FONT_5NORMAL_ID, x+7, y+38, 84, 0, 2, "LCD-8448GR");
  draw_fonts_print_str(DRAW_FONT_5NORMAL_ID, x-2, y+46, 84, 0, 2, "84X48 DISPLAY");
  draw_paint();
}

