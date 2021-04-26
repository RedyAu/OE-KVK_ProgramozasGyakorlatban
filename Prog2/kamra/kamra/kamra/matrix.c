/*
 * matrix.c
 *
 * Created: 2021.04.03. 10:32:20
 *  Author: FAB
 */ 
#include "matrix.h"

void temperatureEntry(uint8_t key) {
	static uint8_t lastKey;
	
	if (key != lastKey) {
		lastKey = key;
		if (key != 99) {
			if (key == 11) { // #
				isDuringEntry = 0;
				lcdBlink(0);
			} else {
				setTemp = (setTemp * 10) + key;
				if (setTemp > 400) setTemp = 400;
				if (setTemp / 100) {
					isDuringEntry = 0;
					lcdBlink(0);
				}
				mainScreenPrint();
			}
		}
	}
}

void initMatrix() {
	DDRC |= 0x78;
}

int readMatrix() {
	/*PINC
	PORTC*/
	uint8_t i;
	uint8_t toReturn = 99;
	
	for (i = 0; i < 4; i++) {
		_delay_ms(5);
		PORTC = 0x01 << (i + 3);
		uint8_t x = PINC & 0x7F;
		
		switch (x) {
			case 0b00001011:
				toReturn = 3;
				break;
			case 0b00001101:
				toReturn = 2;
				break;
			case 0b00001110:
				toReturn = 1;
				break;
			case 0b00010011:
				toReturn = 6;
				break;
			case 0b00010101:
				toReturn = 5;
				break;
			case 0b00010110:
				toReturn = 4;
				break;
			case 0b00100011:
				toReturn = 9;
				break;
			case 0b00100101:
				toReturn = 8;
				break;
			case 0b00100110:
				toReturn = 7;
				break;
			case 0b01000011:
				toReturn = 11;
				break;
			case 0b01000101:
				toReturn = 0;
				break;
			case 0b01000110:
				toReturn = 10;
				break;
		}
	}
	_delay_ms(5);
	return toReturn;
}