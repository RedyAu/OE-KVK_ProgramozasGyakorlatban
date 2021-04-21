/*
 * prog2gyak-10.c
 *
 * Created: 2021. 04. 12. 16:42:57
 * Author : fodor
 */

#define F_CPU 8000000UL
#include <avr/io.h>

void port_init();
void uart_init();
void uart_transmit(unsigned char adat);
unsigned char uart_receive();
void uart_transmit_string(char *string);

int main(void)
{
	unsigned char tmp[10];
	
	unsigned char *menu[6] = {
		"RED LED ON",
		"RED LED OFF",
		"GREEN LED ON",
		"GREEN LED OFF",
		"BLUE LED ON",
		"BLUE LED OFF"
	};
	
	port_init();
	uart_init();
	
	for (int i = 0; i < 6; i++) {
		uart_transmit(i + 1 + '0');
		uart_transmit_string(". ");
		uart_transmit_string(menu[i]);
		uart_transmit_string("\r\n");
	}
    
	unsigned char c;
	
    while (1) 
    {
		switch(c = uart_receive()) {
			case '1': PORTC |= 0x80; break;
			case '2': PORTC &= 0x7F; break;
			case '3': PORTE |= (1<<3); break;
			case '4': PORTE &= (0<<3); break;
			case '5': PORTE |= (1<<2); break;
			case '6': PORTE &= (0<<2); break;
		}
		uart_transmit_string(menu[c - 1 - '0']);
		uart_transmit_string("\r\n");
    }
}

void uart_init() {
	UBRR0H = 0;
	UBRR0L = 51; //
	UCSR0B = (1<<RXEN) | (1<<TXEN);
	UCSR0C = (0<<USBS0) | (1<<UCSZ00) | (1<<UCSZ01);
}

void port_init() {
	DDRC |= 0x80;
}

void uart_transmit(unsigned char adat) {
	while (!(UCSR0A & (1<<UDRE0))); //Ciklusban várakozik amíg nem üres a küldés-buffer
	
	UDR0 = adat;
}

unsigned char uart_receive() {
	while (!(UCSR0A & (1<<RXC))); //Wait for data to arrive
	
	return UDR0;
}

void uart_transmit_string(char *string) {
	int i = 0;
	while (string[i]) {
		uart_transmit(string[i]);
		i++;
	}
}