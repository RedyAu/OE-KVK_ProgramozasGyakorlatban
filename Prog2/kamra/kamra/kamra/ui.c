/*
 * ui.c
 *
 * Created: 2021. 04. 05. 22:23:47
 *  Author: FAB
 */ 

#include "globals.h"
#include "ui.h"
#include "lcd.h"
#include "tempsensor.h"

#include <stdio.h>

long long int hour = 0;
char timeUnit = 0;
int lastOnValue = 0;

int setTemp = 0; //Stores Temperature *10 (1,5C -> 15)

void mainScreenPrint() {
	updateLastOnDisplay();
	currentTemp = readTemp();
	char currentPrint[6] = {0};
	sprintf(currentPrint, "%3d.%1d", currentTemp / 10, currentTemp % 10);
	lcdPrintAt(0x09, 1, currentPrint);
	
	sprintf(currentPrint, "%3d", getOnPercentage());
	lcdPrintAt(0x0B, 3, currentPrint);
	
	sprintf(currentPrint, ((timeUnit != '+') ? "%3d %c" : "40+ d"), lastOnValue, timeUnit);
	lcdPrintAt(0x0B, 4, currentPrint);
	
	sprintf(currentPrint, "%3d.%1d", setTemp / 10, setTemp % 10);
	lcdPrintAt(0x09, 2, currentPrint);
}

unsigned char saveMinute() {
	hour <<= 1; //Only the first 60 bits are checked.
	hour |= isHeating;
}

unsigned char getOnPercentage() {
	long long int tempHour = hour;
	unsigned char percentage = 0;
	
	int i;
	for (i = 0; i < 60; i++) {
		if (tempHour & ((long long int)1)<<i) percentage++;
	}
	
	return (double)percentage / 60 * 100;
}

void updateLastOnDisplay() {
	static unsigned char millisOverflow = 0;
	if (millisOverflow && isHeating) return;
	
	unsigned long difference = millis - lastOn;
	
	if ((lastOn == 0) || (difference < 1000)) {
		timeUnit = 's';
		lastOnValue = 0;
		millisOverflow = 0;
	}
	else if (difference < 60000) {
		timeUnit = 's';
		lastOnValue = difference / 1000;
	}
	else if (difference < 3600000) {
		timeUnit = 'm';
		lastOnValue = difference / 60000;
	}
	else if (difference < 604800000) { //Only switch to showing days after a week
		timeUnit = 'h';
		lastOnValue = difference / 3600000;
	}
	else if (difference < 4294966000) {
		timeUnit = 'd';
		lastOnValue = difference / 86400000;
	}
	else {
		timeUnit = '+';
		millisOverflow = 1;
	}
}