;
; prog2gyak-1.asm
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
.DEF	hazi	=	r22

.ORG	0x00
		rjmp	start

.ORG	0x100
.macro port_init //Az �sszes led ir�nyregisztere: DDRB �s DDRD is 11110000 = 0xF0
		ldi		tmp,	0xF0
		out		DDRB,	tmp
		out		DDRD,	tmp
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
	;ldi		delay3,	0x2A
	ldi		delay3, 0x1A
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

.macro orai
	;eor		led,	tmp2
	rol		LED
.endmacro 

hazi_1:
	
ret

.macro hazi_2

.endmacro

.macro hazi_3

.endmacro

start:
	stack_init
    port_init
	delay_init
	ldi		led,	0x01
	ldi		tmp2,	0x01

loop:
	delay_init
	call	delay_1s
	
	;orai
	call hazi_1
	;hazi_2
	;hazi_3
	
	call	LED_out
    rjmp	loop

	/*
	H�zi:
	1.
	1 kezd��rt�k
	El�sz�r fusson el balra, majd pattanjon vissza jobbra

	2.
	"Night Rider"
	2 sz�ls� led k�z�tt (led 0 led 7) vil�g�tanak
	majd �ssze k�zelednek, majd t�volodnak
	o--- ---o
	-o-- --o-
	--o- -o--
	---o o---
	�s vissza

	3.
	Night rider, csak 2 led egym�s mellett
	oo-- --oo
	-oo- -oo-
	--oo oo--
	�s vissza
	*/