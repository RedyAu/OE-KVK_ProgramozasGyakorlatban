/*
	* kamra.c
	*
	* Created: 2021.04.03. 10:20:24
	* Author : FAB
*/ 

#include <avr/io.h>
#include <stdio.h>
#include <math.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

#include "globals.h"
#include "lcd.h"
#include "matrix.h"
#include "ui.h"
#include "tempsensor.h"

void ledInit();
void timerInit();

#define UpdateRate 1000
#define RelayPort 7

void init() {
	initMatrix();
	ledInit();
	lcdInit();
	tempInit();
	timerInit();
}

int main(void)
{
	init();
	//Print constant screen content
	lcdPrintMulti("Current:       C", "Set:           C", "Last Hour:     %", "Last On:");
	
	while (1) 
	{
		unsigned char showingEasterEgg = 0;
		
		if (pinGPrev != PING) {
			pinGPrev = PING;
			
			switch(pinGPrev) {
				case 0x01:
					isDuringEntry ^= 0x01;
					lcdBlink(isDuringEntry);
					
					//If entry has just begun, reset the set temperature.
					setTemp = setTemp * !isDuringEntry; //Branchless programming™ áíûõüöúóé
					
					mainScreenPrint();
					
					_delay_ms(50); //Primitive debounce
					break;
			}
		}
		
		if (isDuringEntry) {
			uint8_t matrixKey = readMatrix();
			temperatureEntry(matrixKey);
			PORTB |= 0x10;
		} else {
			PORTB &= 0xEF;
		}
		
		if (millis - lastUpdate > UpdateRate) {
			lastUpdate = millis;
			//updateStats();
			mainScreenPrint();
		}
		
		static unsigned long lastSaved = 0;		
		if (millis - lastSaved > 60000) {
			lastSaved = millis;
			saveMinute();
		}
		
		if (isHeating) lastOn = millis;
		
		//PORTB = (((currentTemp < setTemp) ? 0x80 : ((currentTemp > setTemp + 5) ? 0 : PORTB)));
		
		if (isHeating) {
			if (currentTemp > setTemp + 5) {
				isHeating = 0;
				PORTB &= 0x7F;
			}
		} else if (currentTemp < setTemp) {
			isHeating = 1;
			PORTB |= 0x80;
		}
	}
}

void ledInit() {
	DDRB |= 0b11110000;
	DDRD |= 0b11110000;
}

void timerInit() {
	OCR0 = 249;
	TCCR0 = ((1 << WGM01) | (1<<CS01) | (1 << CS00));
	TIMSK |= (1<<OCIE0);
	
	sei();
}

ISR(TIMER0_COMP_vect) { //1ms
	millis++;
}