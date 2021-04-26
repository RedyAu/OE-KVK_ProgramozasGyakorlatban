/*
 * lcd.h
 *
 * Created: 2021.04.03. 10:21:58
 *  Author: FAB
 */ 


#ifndef LCD_H_
#define LCD_H_

#define GREET 1

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

//PROTOTYPES

void lcdBlink(uint8_t state);
void lcdEnable();
void lcdCommand(uint8_t cmd);
void lcdData(uint8_t cmd);
void lcdInit();
uint8_t lcdRow(uint8_t row);
void lcdPrintHere(char * data);
void lcdSetCursor(uint8_t x, uint8_t y);
void lcdPrint(char * data, uint8_t row);
void lcdPrintMulti(char * row1,char * row2,char * row3, char * row4);
void lcdBlink(uint8_t state);
void lcdPrintAt(uint8_t x, uint8_t y, char* data);

//LCD PINS
#define LCD_DB7 _BV(7)
#define LCD_DB6 _BV(6)
#define LCD_DB5 _BV(5)
#define LCD_DB4 _BV(4)
#define LCD_DB3 _BV(7)
#define LCD_DB2 _BV(6)
#define LCD_DB1 _BV(5)
#define LCD_DB0 _BV(4)
#define LCD_EN _BV(3)
#define LCD_RW _BV(2)
#define LCD_RS _BV(1)

//LCD ROW ADDRESSES
#define LCD_ROW1 0x00
#define LCD_ROW2 0x40
#define LCD_ROW3 0x10
#define LCD_ROW4 0x50

//LCD COMMANDS
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_ON 0x0C
#define LCD_BLCURSOR 0x0D
#define LCD_4BIT 0x20
#define LCD_CONF 0x28

#define LCD_CMD_PORT (PORTF)
#define LCD_DATA_PORT (PORTE)

#define lcdClear() lcdCommand(LCD_CLEAR)

#endif /* LCD_H_ */