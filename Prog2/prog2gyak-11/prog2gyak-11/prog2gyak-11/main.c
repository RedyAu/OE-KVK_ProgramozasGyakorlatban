/*
 * prog2gyak-11.c
 *
 * Created: 2021. 04. 19. 17:33:29
 * Author : fodor
 */ 

#include <avr/io.h>

//ANAL�G KONVERTER, TEMPERATURE SENSOR

int main(void)
{
	uint16_t tmp = 0;
	char kiir[10];
    ADC_init(channel, prescaler); //0 bemenetcsatorna, 7-es el�oszt�s (-> katal�gus)
	LCD_str_pos("ADC + LM35 test", x, y);
    while (1) 
    {
		tmp = ADC_conv_start(adc_ch0);
		tmp = tmp / 10; //-> hom C
		itoa(tmp, kiir, 10);
		LCD_str_pos(kiir,x,y);
    }
}

void ADC_init(uint8_t ref, uint8_t clock_prescale) {
	ADMUX |= (ref & 0x03) << REFS0;
	ADCSRA |= 1<<ADEN | (clock_prescale & 0x07) << ADPS0;
}

uint16_t ADC_conv_start(ADC_channel channel) {
	uint16_t eredmeny;
	
	ADMUX |= (channel & 0x07) << MUX0; //csatorna kiv�laszt�s
	ADCSRA |= 1 << ADSC; // konverzi� elind�t�sa
	while (!(ADCSRA & (1 << ADIF))); //v�rakoz�s a konverzi�ra
	eredmeny = (ADCH << 8) | (ADCL); //eredm�ny el��ll�t�sa
	eredmeny = eredmeny * 4096 / 1024;
	return eredmeny;
}