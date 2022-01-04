/*
 * Pelt_uart.c
 *
 *  Created on: Dec 12, 2016
 *      Author: tkowalczyk
 *
 *      Plik obslugujacy wysylanie ciagu znakow poprzes USART
 */

#include "Pelt_uart.h"

int __io_putchar(int c) {
	send_char(c);
	return c;
}

void send_char(char c) {
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
		;
	USART_SendData(USART1, c);
}

void send_string(const char* s) {
	while (*s)
		send_char(*s++);
}
