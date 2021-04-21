/*
 * prog2gyak-7.c
 *
 * Created: 2021. 03. 22. 16:22:10
 * Author : fodor
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t szamol = 0;

void tim0_init(void);
void led_out(uint8_t led) {
	PORTD = led & 0xF0;
	PORTB = (led << 4) & 0xF0;
}
void tim0_OVF_IT_init(void);
void tim0_CTC_OC_IT_init(void);


int main(void)
{
	DDRB = DDRD = 0xF0;
	//tim0_init();
	//tim0_OVF_IT_init();
	tim0_CTC_OC_IT_init();
    while (1) 
    {
		//haha nothing
    }
}
ISR(TIMER0_COMP_vect) { //1ms
	if (szamol == 999) {
		PORTB ^= 0x10;
		szamol = 0;
	} else szamol++;
}

/*
ISR(TIMER0_OVF_vect) {
	//kb every 32 ms
	if (szamol == 30) {
		PORTB ^= 0x10;
		szamol = 0;	
	} else {
		szamol++;
	}
}
*/

void tim0_CTC_OC_IT_init(void) {
	//1MS INTERRUPT
	//mode: CTC WGM01 WGM0 - 1 0
	//Prescale: ??
	//Period: ??
	//1ms -> 1000 Hz
	//8000000 -> 1000 (8000x)
	//1024 a legnagyobb tho!, nem pontos!
	//32-vel leosztva egész marad (250), ezt már tudjuk Compareben kezelni
	//250 -> OCR<250-1
	OCR0 = 249;
	
	TCCR0 = ((1 << WGM01) | (1<<CS01) | (1 << CS00));
	
	
	//OutputCompare InterrupT enable
	//OCIE2 TOIE2 TICIE1 OCIE1A OCIE1B TOIE1 OCIE0 TOIE0	TIMSK
	TIMSK |= (1<<OCIE0);
	//Global IT enable
	sei();
}

void tim0_OVF_IT_init(void) {
	//Mode: Normal		(WGM01	WGM00 -	0	0)
	//Prescale: 1024	(CS02	CS01	CS00 -	1	1	1)
	//	FOC0	WGM00	COM01	COM00	WGM01	CS02	CS01	CS00
	//	7		6		5		4		3		2		1		0
	TCCR0 = ((1<<CS02) | (1<<CS01) | (1<<CS00)); //0b00000111
	//8 000 000 Hz / 1024 = 7812,5 Hz -> 0,128s a counter periódisideje
	//16 000 000HZ / 1024 = 15 625 Hz -> 0,064s
	//0-255 -> 256 számlálás -> 32,768ms (16,384ms)
	
	//OCIE2 TOIE2 TICIE1 OCIE1A OCIE1B TOIE1 OCIE0 TOIE0	TIMSK
	TIMSK |= (1<<TOIE0);
	
	//Global IT Enable
	sei();
}


void tim0_init(void) {
	//Mode: Normal		(WGM01	WGM00 -	0	0)
	//Prescale: 1024	(CS02	CS01	CS00 -	1	1	1)
	//	FOC0	WGM00	COM01	COM00	WGM01	CS02	CS01	CS00
	//	7		6		5		4		3		2		1		0
	TCCR0 = ((1<<CS02) | (1<<CS01) | (1<<CS00)); //0b00000111
	//8 000 000 Hz / 1024 = 7812,5 Hz -> 0,128s a counter periódisideje
	//16 000 000HZ / 1024 = 15 625 Hz -> 0,064s
	//0-255 -> 256 számlálás -> 32,768ms (16,384ms)
}

//HÁZI
//Óra timer interrupttal