.INCLUDE "m128def.inc"      ; Include definitions Atmega128
;.INCLUDE "m64def.inc"       ; Include definitions Atmega64

 .DSEG
  ;
 .CSEG
 .DEF LED = r17
 .DEF BTN = r18
.ORG 0x00
	rjmp start                      	; jump to start
 
.ORG 0x100
;--------------------
; MACRO
;--------------------	
.macro init
	;LED
	ldi r16, 0xF0
	out DDRB, r16
	out DDRD, r16
	eor r16, r16

	;GOMB
	ldi r16, 0x00
	sts DDRG, r16 ;nem is kell, init érték 0
.endmacro	

.macro led_out
	out PORTD, LED
	swap LED
	out PORTB, LED
	swap LED
.endmacro
;--------------------
; SUBRUTINE
;--------------------		
;--------------------
; INTERRUPT
;--------------------		
;--------------------
; PROGRAM
;--------------------		
start:	
;--------------------
; INIT
;--------------------		
init
;--------------------
; PROGRAM
;--------------------		
loop:
		lds BTN, PING
		andi BTN, 0b00011111
		mov LED, BTN
		led_out
		rjmp	loop