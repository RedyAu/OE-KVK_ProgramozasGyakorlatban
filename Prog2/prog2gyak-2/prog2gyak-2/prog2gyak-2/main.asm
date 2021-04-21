;
; prog2gyak-2.asm
;
; Created: 2021. 02. 08. 17:13:43
; Author : fodor
;
.INCLUDE "m128def.inc"
.DSEG

.CSEG
.DEF	tmp		=	r16
.DEF	led		=	r17
.DEF	delay1	=	r18
.DEF	delay2	=	r19
.DEF	delay3	=	r20
.DEF	tmp2	=	r21
.DEF	ertek	=	r23
.DEF	tmp3	=	r24
.DEF	digit	=	r25

.ORG	0x00
		rjmp	start

.ORG	0x100
.macro port_init //Az �sszes led ir�nyregisztere: DDRB �s DDRD is 11110000 = 0xF0
		ldi		tmp,	0xF0 //LEDEK
		out		DDRB,	tmp
		out		DDRD,	tmp

		ldi		tmp,	0xFF //7SEG DP
		out		DDRA,	tmp
.endmacro

.macro stack_init //A stacket a ram v�g�re (RamEnd) kell �ll�tani (AVR-ben nincs hardveres stack)
		ldi		tmp,	high(RAMEND) //high: a fels� bitjei
		out		SPH,	tmp //k�l�n kell a fels� �s az als� biteket be�ll�tani
		ldi		tmp,	low(RAMEND)
		out		SPL,	tmp //SPL = StackPointerLow, stb
.endmacro

.macro delay_init
	ldi		delay1,	0xFF
	ldi		delay2,	0xFF
	ldi		delay3,	0x2A
	;ldi		delay3, 0x1A
.endmacro

LED_out:
	out		PORTD,	led
	swap	LED //Mivel a LED regiszter�nk als� n�gy bitj�t a PORTB regiszter fels� n�gy bitj�re kell ki�rnunk, az als� �s fels� n�gy bitet megcser�lj�k.
	out		PORTB,	led
	swap	LED
ret

delay_1s:
	dec		delay1
	brne	delay_1s
	dec		delay2
	brne	delay_1s
	dec		delay3
	brne	delay_1s
ret

seven_segment:
	eor tmp3, tmp3 //kiz�r� vagy: mindegyik 0 lesz
	swap digit
	or tmp3, digit
	swap digit
	or tmp3, led
	ori tmp3, 0x80
	out porta, tmp3
ret

start:
	stack_init
    port_init
	delay_init
	ldi		led,	1
	ldi		tmp2,	0x01
	ldi		digit, 1
	ldi		ertek, 5

loop:
	delay_init
	call	delay_1s
	eor		LED, tmp2
	call	LED_out

	call	seven_segment
	inc		digit
	andi	digit, 0x03
kiir:
	call seven_segment
	rjmp loop

	/*
	H�zi:
	Mind a n�gy sz�mjegyen l�tsz�djon a ki�rt �rt�k
	�rjuk ki hogy '1234'
	Javaslat: haszn�ljunk t�mb�t??

	*/