/*
 * globals.h
 *
 * Created: 2021. 04. 24. 22:57:33
 *  Author: fodor
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <avr/sfr_defs.h>

extern uint8_t isDuringEntry;

extern uint8_t pinGPrev;

extern unsigned long millis;
extern unsigned long lastUpdate;
extern unsigned long lastOn;

extern uint8_t isHeating;

extern char timeUnit;

#endif /* GLOBALS_H_ */