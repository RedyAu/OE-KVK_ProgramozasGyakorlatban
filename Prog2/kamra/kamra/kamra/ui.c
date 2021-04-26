/*
 * ui.c
 *
 * Created: 2021. 04. 05. 22:23:47
 *  Author: FAB
 */ 

#include "ui.h"
#include "lcd.h"
#include "tempsensor.h"
#include <stdio.h>

uint32_t hour = 0;

int setTemp = 0; //Stores Temperature *10 (1,5C -> 15)

void mainScreenPrint() {
	currentTemp = readTemp();
	char currentPrint[6] = {0};
	sprintf(currentPrint, "%3d.%1d", currentTemp / 10, currentTemp % 10);
	lcdPrintAt(0x09, 1, currentPrint);
	
	sprintf(currentPrint, "%3d.%1d", setTemp / 10, setTemp % 10);
	lcdPrintAt(0x09, 2, currentPrint);
}

unsigned char saveMinute() {
	hour <<= 1;
}

unsigned char getOnPercentage() {
	
}