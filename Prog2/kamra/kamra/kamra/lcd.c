/*
 * lcd.c
 *
 * Created: 2021.04.03. 10:21:07
 *  Author: FAB
 */ 

#include "lcd.h"

void lcdEnable(){
	LCD_CMD_PORT &= ~LCD_EN;
	_delay_us(5);
	LCD_CMD_PORT |= LCD_EN;
	_delay_us(5);
	LCD_CMD_PORT &= ~LCD_EN;
	_delay_us(5);
}

void lcdCommand(uint8_t cmd){
	_delay_ms(2);
	PORTF &= ~LCD_RW;
	PORTF &= ~LCD_RS;
	
	LCD_DATA_PORT &= ~(0xF0);
	PORTE |= cmd&0xF0;
	lcdEnable();
	LCD_DATA_PORT &= ~(0xF0);
	PORTE |= (cmd<<4)&0xF0;
	lcdEnable();
}

void lcdData(uint8_t cmd){
	_delay_ms(2);
	LCD_CMD_PORT &= ~LCD_RW;
	LCD_CMD_PORT |= LCD_RS;
	
	LCD_DATA_PORT &= ~(0xF0);
	LCD_DATA_PORT |= cmd&0xF0;
	lcdEnable();
	LCD_DATA_PORT &= ~(0xF0);
	LCD_DATA_PORT |= (cmd<<4)&0xF0;
	lcdEnable();
}

void lcdInit(){
	DDRE |= 0xF0;
	DDRF |= LCD_EN|LCD_RW|LCD_RS;
	PORTF &= ~LCD_RW;
	_delay_ms(15);
	//lcd_sendcmd(LCD_4BIT);
	PORTF &= ~LCD_RS;
	PORTF &= ~LCD_RW;
	PORTE|=0x20;
	lcdEnable();
	lcdEnable();
	lcdEnable();
	
	lcdCommand(LCD_CONF);
	lcdCommand(LCD_CONF);
	lcdCommand(LCD_CONF);
	lcdCommand(0x02);
	lcdCommand(LCD_CLEAR);
	lcdCommand(LCD_ON);
}

uint8_t lcdRow(uint8_t row){
	switch(row){
		case 0: case 1: return LCD_DB7|LCD_ROW1; break;
		case 2: return LCD_DB7|LCD_ROW2; break;
		case 3: return LCD_DB7|LCD_ROW3; break;
		case 4: return LCD_DB7|LCD_ROW4; break;
	}
}

void lcdPrintHere(char * data){
	uint8_t i=0;
	while(i<16&&*data!='\0'){
		lcdData(*(data++));
		i++;
	}
}

void lcdPrintAt(uint8_t x, uint8_t y, char* data) {
	lcdSetCursor(x, y);
	lcdPrintHere(data);
}

void lcdSetCursor(uint8_t x, uint8_t y){
	lcdCommand(lcdRow(y)+x);
}

void lcdPrint(char * data, uint8_t row){
	lcdSetCursor(0,row);
	lcdPrintHere(data);
}


void lcdPrintMulti(char * row1,char * row2,char * row3, char * row4){
	lcdPrint(row1,1);
	lcdPrint(row2,2);
	lcdPrint(row3,3);
	lcdPrint(row4,4);
}

void lcdBlink(uint8_t state){
	if(state) lcdCommand(LCD_BLCURSOR);
		else  lcdCommand(LCD_ON);
}
