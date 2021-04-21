#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>


#define LCD_RS	(PF1)
#define LCD_RW	(PF2)
#define LCD_E	(PF3)

#define LCD_CMD_DDR	(DDRF)
#define LCD_DATA_DDR	(DDRE)

#define LCD_CMD_PORT (PORTF)
#define LCD_DATA_PORT (PORTE)

void LCD_init();
void LCD_command(uint8_t cmd);
void LCD_data(uint8_t data);
void LCD_enable();
void LCD_str(uint8_t *t);
void LCD_pos(uint8_t x, uint8_t y);

int main(void)
{
	LCD_init();
	LCD_command(0x01);
	LCD_pos(1,1);
	LCD_str("b
	lma\0");
	while (1)
	{
	}
}

void LCD_init(void)
{
	LCD_DATA_DDR |= 0xF0;
	LCD_CMD_DDR |= 1<<LCD_RS | 1<<LCD_RW | 1<<LCD_E;
	PORTF &= ~(LCD_RW);
	PORTF &= ~(LCD_RS);
	PORTE = 0x20; // 4. bites
	LCD_enable();
	LCD_enable();
	LCD_enable();
	LCD_command(0x28); //4. bites 2 soros
	LCD_command(0x28);
	LCD_command(0x28);
	LCD_command(0x02); // kurzor alaphelyzetbe állítása
	LCD_command(0x01); // képernyõ törlés
	LCD_command(0x0F); // képernyõ be, kurzor be, kurzor villog
	
}
void LCD_enable()
{
	LCD_CMD_PORT |= 1<<LCD_E;
	_delay_us(2);
	LCD_CMD_PORT &= ~(1<<LCD_E);
	_delay_us(2);

}

void LCD_command(uint8_t cmd)
{
	_delay_ms(2);
	LCD_CMD_PORT &= ~(1<<LCD_RS); //command
	LCD_CMD_PORT &= ~(1<<LCD_RW);
	LCD_CMD_PORT &= ~(1<<LCD_E);
	
	LCD_DATA_PORT &= ~(0xF0);
	LCD_DATA_PORT |= cmd & 0xF0;
	LCD_enable();
	LCD_DATA_PORT &= ~(0xF0);
	LCD_DATA_PORT |= (cmd<<4) & 0xF0;
	LCD_enable();
}
void LCD_data(uint8_t data)
{
	_delay_ms(2);
	LCD_CMD_PORT |=  (1<<LCD_RS); //data
	LCD_CMD_PORT &= ~(1<<LCD_RW);
	LCD_CMD_PORT &= ~(1<<LCD_E);
	
	LCD_DATA_PORT &= ~(0xF0);
	LCD_DATA_PORT |= data & 0xF0;
	LCD_enable();
	LCD_DATA_PORT &= ~(0xF0);
	LCD_DATA_PORT |= (data<<4) & 0xF0;
	LCD_enable();
}

void LCD_str(uint8_t *t) {
	uint8_t i = 0;
	while (*t) { //amíg nem NULL
		LCD_data(*t);
		i++;
	}
}
void LCD_pos(uint8_t x, uint8_t y) {
	//1. sor 0x00-0x0F
	//2. sor 0x40-0x4F
	//3. sor 0x10-0x1F
	//4. sor 0x50-0x5F
	
	switch (x) {
		case 1:
			LCD_command((0x80 | 0x00) + y);
			break;
		case 2:
			LCD_command((0x80 | 0x40) + y);
			break;
		case 3:
			LCD_command((0x80 | 0x10) + y);
			break;
		case 4:
			LCD_command((0x80 | 0x50) + y);
			break;
	}
}