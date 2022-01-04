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
** 	jest uzyskanie stabilnej i trwa³ej temperatury w konkretnym obszarze pomiarowym.
** 	G³ównym zastosowaniem regulatora bêdzie wykorzystanie go do kalibracji
** 	zewnêtrznych czujników temperatury i badanie ich dok³adnoœci w ró¿nych
** 	temperaturach. Przewidywany zakres uzyskiwalnych temperatur mieœci siê
** 	w przedziale <-10;70>°C . Zmiana temperatury pomiêdzy
** 	granicznymi mo¿liwymi temperaturami powinna nie trwaæ d³u¿ej ni¿ minutê.
**
**
**	Wykaz realizowanych finkcji:
**	Regulacja temperatury w komorze pomiarowej
**	Wyœwietlanie aktualnej temperatury i ustalonej temperatury na wyœwietlaczu LCD
**	Mo¿liwoœæ wyboru konkretnej po¿¹danej temperatury z dostêpnego przedzia³u za pomoc¹ 2 przycisków,
**	regulacja skokowa oraz p³ynna przy przytrzymaniu przycisku.
**	Odczyt temperatury komory pomiarowej z dok³adnoœci¹ do 2 °C
**	Mo¿liwoœæ wyboru ¿¹danej temperatury z rozdzielczoœci¹ 0,1°C
**	Wysy³anie aktualnej i ¿¹danej temperatury do komputera PC za pomoc¹
**	portu szeregowego( Dane wysy³ane poprzez UART i konwertowane do formatu USB poprzez zewnêtrzny konwerter).
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

