/*
 * prog2gyak-4.c
 *
 * Created: 2021. 03. 01. 17:29:27
 * Author : fodor
 */ 

#include <avr/io.h>

//Delay init
#define F_CPU 8000000
#include <util/delay.h>

void ledOut(unsigned char led);
void portInit();
unsigned char runLeft(unsigned char led);
unsigned char runRight(unsigned char led);
unsigned char backAndForth(unsigned char led);
unsigned char nightRider(unsigned char led);
void sevenSegment(unsigned int ertek);

int main(void)
{
    portInit();
	unsigned char led = 0x01;
	
	unsigned char button = 0x00;
	while(1) {
		static unsigned char oldButton;
		oldButton = button;
		button = PING ? PING : button;
		if (oldButton != button) {
			if (!((oldButton == 1 || oldButton == 2) && (button == 1 || button == 2))) led = 0x01;
		}
		oldButton = button;
		switch(button) {
			case 1:
				led = runLeft(led);
				ledOut(led);
				_delay_ms(100);
				break;
			case 2:
				led = runRight(led);
				ledOut(led);
				_delay_ms(100);
				break;
			case 4:
				led = backAndForth(led);
				ledOut(led);
				_delay_ms(100);
				break;
			case 8:
				led = nightRider(led);
				ledOut(led);
				_delay_ms(100);
				break;
			case 16:
				sevenSegment(1234);
				_delay_ms(1);
				break;
			default:
				ledOut(0);
				break;
		}
	}
	return 0;
}

unsigned char runLeft(unsigned char led) {
	if (led & 0x80) led = 0x01;
	else led = led << 1; 
	return led;
}
unsigned char runRight(unsigned char led) {
	if (led & 0x01) led = 0x80;
	else led = led >> 1;
	return led;
}
unsigned char backAndForth(unsigned char led) {
	static unsigned char direction = 0x01;
	if (direction) {
		if (led & 0x80) direction = 0;
		else {
			led = led << 1;
			return led;
		}
	} 
	if (led & 0x01) {
		direction = 1;
		return led;
	}
	else led = led >> 1;
	return led;
}
unsigned char nightRider(unsigned char led) {
	static unsigned char led1 = 0x01, led2 = 0x80;
	
	if (led1 == 0x80) led1=0x01;
	else led1 = led1 << 1;
	
	if (led2 == 0x01) led2=0x80;
	else led2 = led2 >> 1;
	
	return led1 | led2;
}
void sevenSegment(unsigned int ertekO) {
	static unsigned char digit = 4;
	static unsigned int ertek;
	if (digit < 4) {
		PORTA = 0x80 | digit << 4 | ertek % 10;
		ertek = ertek / 10;
		digit++;
	} else {
		digit = 0;
		ertek = ertekO;
	}
	return;
}

void ledOut(unsigned char led) {
	PORTD = led;
	PORTB = led << 4;
}

void portInit() {
	DDRA = 0xFF;
	DDRD = 0xF0;
	DDRB = 0xF0;
	DDRG = 0x00;
}