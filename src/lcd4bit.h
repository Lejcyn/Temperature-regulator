#include "stm32f10x.h"

#define LCD_D4 	           ((u16)0x0008)  /// PC3#define LCD_D5             ((u16)0x0004)  /// PC2#define LCD_D6 			   ((u16)0x0002)  /// PC1#define LCD_D7             ((u16)0x0001)  /// PC0#define LCD_D_ALL          ((u16)0x000F)  /// PC0, PC1, PC2, PC3#define LCD_RS             ((u16)0x1000)  /// PC12#define LCD_RW             ((u16)0x0800)  /// PC11#define LCD_EN              ((u16)0x0400)  /// PC10
uint8_t LCD_ReadByte(void);
void LCD_SendByte(uint8_t cmd);
void LCD_SendCmd(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_SendText(uint8_t * text);
void LCD_Clear(void);
void LCD_GoTo(uint8_t wers, uint8_t kol);
void LCD_Init(void);
