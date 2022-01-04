#include "stm32f10x.h"

#define LCD_D4 	           ((u16)0x0008)  /// PC3
uint8_t LCD_ReadByte(void);
void LCD_SendByte(uint8_t cmd);
void LCD_SendCmd(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_SendText(uint8_t * text);
void LCD_Clear(void);
void LCD_GoTo(uint8_t wers, uint8_t kol);
void LCD_Init(void);