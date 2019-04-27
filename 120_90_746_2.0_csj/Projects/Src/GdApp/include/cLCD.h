#include "stm32f7xx_hal.h"
#include "cbase.h"
#ifndef _cLCD_

#define LCD_ADDR_BASE 				(0x6c000000)
#define LCD_COMMAND_ADDR			(LCD_ADDR_BASE+0x0)
#define LCD_DATA_ADDR				(LCD_ADDR_BASE+0x2)
#define LCD_COMMAND_COMMENT			(0x2C)

#define LCD_WIDTH 	320
#define LCD_HEIGHT 	240
#define LCD_PIXELs 	(LCD_WIDTH*LCD_HEIGHT)


void LCD_Clear(uint32_t Color);
void LCD_SetPoint(u16 x,u16 y,u16 point);
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);//¹â±ê;
void LCD_Mode(u8 mode);
unsigned short LCD_read_data(void);
void LCD_write_data(__IO uint16_t i);
void LCD_write_command(__IO uint16_t i);
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
void delay_(__IO uint32_t nCount);


void test_color(uint32_t r,uint32_t g,uint32_t b);
void test_moveBar(void);


#endif


