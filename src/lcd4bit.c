/*
 * lcd4bit.c
 *
 *  Created on: Dec 12, 2016
 *      Author: tkowalczyk
 *
 *      Biblioteka zewnetrzna sluzaca do obslugi wyswietlacza LCD
 *
 *      Wykorzystany sterownik HD44780
 *
 *      Interfejs 4-bitowy
 */


#include "lcd4bit.h"
void delay_ms(int ms)
{
	int i, tms;
	tms = 2000*ms;
	for(i=0;i<tms;i++);
}

void delay_us(int us)
{
	int i, tus;
	tus = 2*us;
	for(i=0;i<tus;i++);
}
void delaymikrose(int us)
{
	int tus;
	int k;
	tus = 2*us;
	for(k=0;k<tus;k++);
}
void delaymilise(int ms)
	{
		int  tms;
		int k=0;
		tms = 2000*ms;
		for(k=0;k<tms;k++);
	}
uint8_t LCD_ReadByte(void)
{
	GPIO_InitTypeDef GPIO_Conf;
	uint8_t ReadedData=0;
	GPIO_SetBits(GPIOC, LCD_D_ALL); 
	/// Zmiana konfiguracji wyprowadzen na wejsciach
  	GPIO_Conf.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  	GPIO_Conf.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Conf.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_Conf);

  	GPIO_SetBits(GPIOC, LCD_RW);
	GPIO_SetBits(GPIOC, LCD_EN);

	if(GPIO_ReadInputDataBit(GPIOC, LCD_D7))	///odczyt starszej polowy
		ReadedData |= 0x80;
	if(GPIO_ReadInputDataBit(GPIOC, LCD_D6))
		ReadedData |= 0x40; 
	if(GPIO_ReadInputDataBit(GPIOC, LCD_D5))
		ReadedData |= 0x20; 
	if(GPIO_ReadInputDataBit(GPIOC, LCD_D4))
		ReadedData |= 0x10;  

	GPIO_ResetBits(GPIOC, LCD_EN);
	delay_us(10);
	GPIO_SetBits(GPIOC, LCD_EN);

	if(GPIO_ReadInputDataBit(GPIOC, LCD_D7))	///odczyt mlodszej polowy
		ReadedData |= 0x08;
	if(GPIO_ReadInputDataBit(GPIOC, LCD_D6))
		ReadedData |= 0x04; 
	if(GPIO_ReadInputDataBit(GPIOC, LCD_D5))
		ReadedData |= 0x02; 
	if(GPIO_ReadInputDataBit(GPIOC, LCD_D4))
		ReadedData |= 0x01;  
	GPIO_ResetBits(GPIOC, LCD_EN);
	/// Powrot do pierwotnych ustawien wyprowadzen
  	GPIO_Conf.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  	GPIO_Conf.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_Conf.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_Conf);	

	return ReadedData;
}


void LCD_SendByte(uint8_t cmd)
{
	uint8_t tcmd = 0;

	GPIO_ResetBits(GPIOC, LCD_RW);
	GPIO_ResetBits(GPIOC, LCD_D_ALL); 	
	GPIO_SetBits(GPIOC, LCD_EN); 

	tcmd = cmd >> 4;			 		/// 4x w prawo
	if( tcmd & 0x01 )		
		GPIO_SetBits(GPIOC, LCD_D4);	///zapis starszej polowy
	if( tcmd & 0x02 )		
		GPIO_SetBits(GPIOC, LCD_D5);
	if( tcmd & 0x04 )		
		GPIO_SetBits(GPIOC, LCD_D6);	
	if( tcmd & 0x08 )		
		GPIO_SetBits(GPIOC, LCD_D7);	

	GPIO_ResetBits(GPIOC, LCD_EN); 
	delay_us(10);								
	GPIO_SetBits(GPIOC, LCD_EN); 
	GPIO_ResetBits(GPIOC, LCD_D_ALL); 	

	cmd &= 0x0F;	  			/// maskowanie czterech mlodszych bitow
	if( cmd & 0x01 )		
		GPIO_SetBits(GPIOC, LCD_D4);	///zapis mlodszej polowy
	if( cmd & 0x02 )		
		GPIO_SetBits(GPIOC, LCD_D5);
	if( cmd & 0x04 )		
		GPIO_SetBits(GPIOC, LCD_D6);
	if( cmd & 0x08 )		
		GPIO_SetBits(GPIOC, LCD_D7);			

	GPIO_ResetBits(GPIOC, LCD_EN); 
	GPIO_ResetBits(GPIOC, LCD_D_ALL); 
	GPIO_ResetBits(GPIOC, LCD_RS);
	while(LCD_ReadByte() & 0x80);		/// czekaj na zakonczenie operacji
}

void LCD_SendCmd(uint8_t cmd)
{
	GPIO_ResetBits(GPIOC, LCD_RS);
	LCD_SendByte(cmd);
}

void LCD_SendData(uint8_t data)
{
	GPIO_SetBits(GPIOC, LCD_RS);
	LCD_SendByte(data);
}

void LCD_SendText(uint8_t * text)
{
	while(*text)
	{
		LCD_SendData(*text);
		text++;
	}
}

void LCD_Clear(void)
{	
	LCD_SendCmd(0x01);
}

void LCD_GoTo(uint8_t wers, uint8_t kol)
{
	uint8_t pos = 0;
	pos = (wers * 0x40) + kol;
	pos += 0x80;
	LCD_SendCmd(pos); 
}

void LCD_Init(void)
{
	uint8_t i;
	GPIO_InitTypeDef GPIO_Conf;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  	GPIO_Conf.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  	GPIO_Conf.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Conf.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_Conf);

	GPIO_ResetBits(GPIOC, LCD_RS);
	GPIO_ResetBits(GPIOC, LCD_EN);
	for(i = 0; i<3; i++)
	{
		GPIO_SetBits(GPIOC, LCD_EN); 
		GPIO_SetBits(GPIOC, LCD_D4 | LCD_D5);
		GPIO_ResetBits(GPIOC, LCD_D6 | LCD_D7);
		GPIO_ResetBits(GPIOC, LCD_EN);
		delay_ms(5);
	}
	GPIO_SetBits(GPIOC, LCD_EN); 
	GPIO_SetBits(GPIOC, LCD_D5);
	GPIO_ResetBits(GPIOC,LCD_D4 | LCD_D6 | LCD_D7);
	GPIO_ResetBits(GPIOC, LCD_EN);
	delaymikrose(100);
	LCD_SendCmd(0x28);
	delaymikrose(100);
	LCD_SendCmd(0x08);
	delaymikrose(100);
	LCD_SendCmd(0x01);
	delaymilise(3);
	LCD_SendCmd(0x06);
	delaymikrose(100);
	LCD_SendCmd(0x0C);
	delaymikrose(100);
}
