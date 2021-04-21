/*
 * tempsensor.c
 *
 * Created: 2021.04.03. 10:22:34
 *  Author: FAB
 */ 

#include "tempsensor.h"

int currentTemp = 0;

void tempInit(){
	ADMUX = (1<<REFS0);
	ADCSRA = ADEN | ADPRESCAL;
	//ADMUX |= ;
}

float readAdc(){
	
	//start ADC conversion
	ADCSRA |= ADSC;
	//wait for it to complete
	while(ADCSRA&ADSC) ;
	//do it again
	ADCSRA |= ADSC; while(ADCSRA&ADSC) ;
	return (ADCL|(ADCH<<8));
}

int readTemp(){
	return (int)(((readAdc()/1024.0)*5000) - 5);
}