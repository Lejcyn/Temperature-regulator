/**
*****************************************************************************
**
**  File        : main.c
**
**  Author      : Tomasz Kowalczyk
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO/STM32
**                STMicroelectronics STM32F10x Standard Peripherals Library
**
**  Distribution: The file is distributed "as is", without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. This file may only be built (assembled or compiled and linked)
**  using the Atollic TrueSTUDIO(R) product. The use of this file together
**  with other tools than Atollic TrueSTUDIO(R) is not permitted.
**
**
** 	Regulator temperatury z wykorzystaniem ogniwa Peltiera. Zadaniem regulatora
** 	jest uzyskanie stabilnej i trwa�ej temperatury w konkretnym obszarze pomiarowym.
** 	G��wnym zastosowaniem regulatora b�dzie wykorzystanie go do kalibracji
** 	zewn�trznych czujnik�w temperatury i badanie ich dok�adno�ci w r�nych
** 	temperaturach. Przewidywany zakres uzyskiwalnych temperatur mie�ci si�
** 	w przedziale <-10;70>�C . Zmiana temperatury pomi�dzy
** 	granicznymi mo�liwymi temperaturami powinna nie trwa� d�u�ej ni� minut�.
**
**
**	Wykaz realizowanych finkcji:
**	Regulacja temperatury w komorze pomiarowej
**	Wy�wietlanie aktualnej temperatury i ustalonej temperatury na wy�wietlaczu LCD
**	Mo�liwo�� wyboru konkretnej po��danej temperatury z dost�pnego przedzia�u za pomoc� 2 przycisk�w,
**	regulacja skokowa oraz p�ynna przy przytrzymaniu przycisku.
**	Odczyt temperatury komory pomiarowej z dok�adno�ci� do 2 �C
**	Mo�liwo�� wyboru ��danej temperatury z rozdzielczo�ci� 0,1�C
**	Wysy�anie aktualnej i ��danej temperatury do komputera PC za pomoc�
**	portu szeregowego( Dane wysy�ane poprzez UART i konwertowane do formatu USB poprzez zewn�trzny konwerter).
**
**
*****************************************************************************
*/

/* Includes */
#include <stdio.h>
#include "Init_all.h"

char wynik[8];///<  Tablica przechowujaca ciag znakow wysylany do LCD
char wynikel[8];///<  Tablica przechowujaca ciag znakow wysylany do LCD
char wynik2[8];///<  Tablica przechowujaca ciag znakow wysylany do LCD
float calka = 0;///<Zmienna przechowujaca wspolczynnik calkowy PID
float rozniczka = 0;///<Zmienna przechowujaca wspolczynnik rozniczkowy PID
int a;///<Zmienna pomocnicza
int ADC1Val = 0;///< Zmienna przechowujaca dane z ADC
int czy = 0;///<Zmienna pomocnicza
int dosredniej[10];///< Tablica zmiennych typu int do usredniania danych wysylanych do LCD
int flaga = 0;//Flaga grzania/chlodzenia
int licznik = 0;///<Zmienna pomocnicza
int odl = 0;///<Uchyb miedzy nastawami a temperatura aktualna
int odl1 = 0;///<Zmienna pomocnicza
int speed = 0;//wypelnienie PWM
int temp1 = 0;///<Czesc calkowita temperatury aktualnej
int temp2 = 0;///<Czesc ulamkowa temperatury aktualnej
int tempmV;///<Temperatura wyrazona w mV
int ustpocz;///<Zmienna pomocnicza do obliczania zmiany nastaw
int ustkon;///<Zmienna pomocnicza do obliczania zmiany nastaw
int ustdelta;///<Zmienna pomocnicza do obliczania zmiany nastaw
int ustaw = 50;//temperatura poczatkowa
int ustaw1 = 0;///<Czesc calkowita temperatury ustawionej
int ustaw2 = 0;///<Czesc ulamkowa temperatury ustawionej
int wartosc_akt = 0;///<Zmienna pomocnicza
int wartosc_ust = 0;///<Zmienna pomocnicza
int zmienna = 0;///<Zmienna pomocnicza

void main() {
	init_wszystko();
	while (1) {
	}
}

