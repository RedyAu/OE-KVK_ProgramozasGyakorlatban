/*
 * ui.h
 *
 * Created: 2021. 04. 05. 22:24:07
 *  Author: FAB
 */ 


#ifndef UI_H_
#define UI_H_

#include <avr/sfr_defs.h>

void mainScreenPrint();
void setScreenPrint();

unsigned char getOnPercentage();

unsigned char saveMinute();



#endif /* UI_H_ */