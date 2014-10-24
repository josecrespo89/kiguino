/*
 * Sparkfun7SD.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: Konstantin Gredeskoul
 *
 *  (c) 2014 All rights reserved.  Please see LICENSE.
 */

#include "Sparkfun7SD.h"

void Sparkfun7SD::clear() {
	beginWrite();
	write((byte) 0);
	write(0x76); 			// Reset the display - this forces the cursor to return to the beginning of the display
	endWrite();
}

void Sparkfun7SD::brightness(uint8_t value) {
	beginWrite();
	write(0x7A);            // Brightness control command
	write(value);           // 0% is dimmest, 100% is brightest
	endWrite();
}
void Sparkfun7SD::printUnits(float value, char *type) {
	clear();

	beginWrite();
	write(0x79); 			// Send the Move Cursor Command
	write(0x04);			// first digit

	char buffer[DIGITS];
	uint8_t decimal = (int) (10.0 * (value - ((int) value)));
	sprintf(buffer, "%2d%d%s", (int) value, decimal, type);
	print(buffer);
	endWrite();

	decimals((byte) (APOSTROPHE | DECIMAL2));
}

void Sparkfun7SD::printTime(uint8_t hours, uint8_t minutes, bool colonShown) {
	uint8_t h = hours % 12;
	if (h == 0) {
		h = 12;
	}
	char buffer[DIGITS];
	sprintf(buffer, "%2d%02d", h, minutes);
	clear();
	print(buffer);
	if (colonShown)
		decimals(COLON);
	else
		decimals(0b000000);

}

void Sparkfun7SD::decimals(byte bitmask) {
	beginWrite();
	write(0x77);
	write(bitmask);
	endWrite();
}
