/*
	* kamra.c
	*
	* Created: 2021.04.03. 10:20:24
	* Author : FAB
	*/ 

#include "lcd.h"
#include "matrix.h"
#include "ui.h"
#include "tempsensor.h"

#include <avr/io.h>
#include <stdio.h>
#include <math.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

uint8_t isDuringEntry = 0;

uint8_t pinGPrev = 0;

uint32_t millis = 0;
uint32_t lastUpdate = 0;

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
	_Greet();
	
	while (1) 
	{
		/*int temp = (int)readTemp();
		char asd[17] = {0};
		sprintf(asd,"%d",temp);
		lcdPrint(asd,1);*/
		
		if (pinGPrev != PING) {
			pinGPrev = PING;
			
			switch(pinGPrev) {
				case 0x01:
					isDuringEntry ^= 0x01;
					setTemp *= !isDuringEntry;
					lcdBlink(isDuringEntry);
					mainScreenPrint();
					
					ledOut(isDuringEntry);
					_delay_ms(10);
					break;
				case 0b00010101:
					//TODO Easter egg
					break;
			}
		}
		
		if (isDuringEntry) {
			uint8_t matrixKey = readMatrix();
			temperatureEntry(matrixKey);
		}
		
		if (millis - lastUpdate > UpdateRate) {
			lastUpdate = millis;
			//updateStats();
			mainScreenPrint();
		}
		
		PORTB = (((currentTemp < setTemp) ? 0x80 : ((currentTemp > setTemp + 5) ? 0 : PORTB)));
		
		//ledOut(isDuringEntry);
		/*
		char asd[17] = {0};
		sprintf(asd,"%d", setTemp);
		lcdPrint(asd, 1);*/
	}
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