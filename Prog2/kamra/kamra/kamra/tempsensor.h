/*
 * tempsensor.h
 *
 * Created: 2021.04.03. 10:22:45
 *  Author: FAB
 */ 


#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_

#include <avr/io.h>

extern int currentTemp;

#define LM35 _BV(0)
#define LM35port PORTF
#define ADEN _BV(7)
#define ADFR _BV(5)
#define ADLAR _BV(5)
#define ADSC _BV(6)
#define ADPRESCAL 0x07 //max 0x07



#endif /* TEMPSENSOR_H_ */