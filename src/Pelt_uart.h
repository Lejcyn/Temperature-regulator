/*
 * Pelt_uart.h
 *
 *  Created on: Dec 12, 2016
 *      Author: tkowalczyk
 */

#include "stm32f10x.h"
int __io_putchar(int c);
void send_char(char c);
void send_string(const char* s);
