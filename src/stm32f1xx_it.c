/**
 ******************************************************************************
 * @file    stm32f1xx_it.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    11-February-2014
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_it.h"

/** @addtogroup IO_Toggle
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern float calka;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M Processor Exceptions Handlers                          */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void) {
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void) {
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void) {
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void) {
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void) {
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void) {
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void) {
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void) {
}

void EXTI0_IRQHandler() {
	if (EXTI_GetITStatus(EXTI_Line0)) {
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0) { ///< jesli przycisk jest przycisniety
			GPIO_ResetBits(GPIOC, GPIO_Pin_9);
			calka = calka / 2;
		}

		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */

void SysTick_Handler(void) {
}
/************************************************
 * Glowna petla programu- pomiar oraz decyzja o mocy podawanej na ogniwo
 ***********************************************/
void TIM2_IRQHandler(void) {
// Sprawdzenie przerwania
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
/// Wyswietlanie dzialania timera
/// PIN C8
		if (GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_8))
			GPIO_ResetBits(GPIOC, GPIO_Pin_8);
		else
			GPIO_SetBits(GPIOC, GPIO_Pin_8);
	}
/// Pomiar temperatury
	ADC1Val = ADC_GetConversionValue(ADC1) * 0.805;
	wartosc_akt = ADC1Val;

///Usrednianie wartosci wyswietlanej
	dosredniej[licznik] = ADC1Val;
	licznik++;
	if (licznik >= 10)
		/// Co 10 zebranych pomiarow nastepuje usrednianie
			{
		licznik = 0;
		for (int r = 0; r < 9; r++) {
			ADC1Val = ADC1Val + dosredniej[r];
		}
		ADC1Val = ADC1Val / 10;

		zmienna = ADC1Val;

		if (ADC1Val < 2108) ///temperatury ujemne
				{
			/// obliczanie temperatury aktualnej
			ADC1Val = 2108 - ADC1Val;
			tempmV = ADC1Val;
			temp1 = ADC1Val * 100 / 1700;
			a = ADC1Val * 10000 / 1700;
			temp2 = a - (100 * temp1);
			if (temp1 > 9) ///formatowanie wyswietlania
				sprintf(wynik, "Akt. Temp. -%d,%d", temp1, (uint16_t) temp2); ///wyswietlanie temperatury aktualnej
			else
				sprintf(wynik, "Akt. Temp.  -%d,%d", temp1, (uint16_t) temp2); ///wyswietlanie temperatury aktualnej
		} else { ///jesli temperatura >0
				 ///obliczanie temperatury aktualnej
			ADC1Val = ADC1Val - 2108;
			tempmV = ADC1Val;
			temp1 = ADC1Val * 100 / 1700;
			a = ADC1Val * 10000 / 1700;
			temp2 = a - (100 * temp1);
			if (temp1 > 9) {	  			///formatowanie wyswietlania
				if (temp2 > 10)
					sprintf(wynik, "Akt. Temp.  %d,%d", (uint16_t) temp1,
							(uint16_t) temp2);///wyswietlanie temperatury aktualnej
				else
					sprintf(wynik, "Akt. Temp.  %d,0%d", (uint16_t) temp1,
							(uint16_t) temp2);///wyswietlanie temperatury aktualnej
			} else {
				if (temp2 > 10)
					sprintf(wynik, "Akt. Temp.   %d,%d", (uint16_t) temp1,
							(uint16_t) temp2);///wyswietlanie temperatury aktualnej
				else
					sprintf(wynik, "Akt. Temp.   %d,0%d", (uint16_t) temp1,
							(uint16_t) temp2);///wyswietlanie temperatury aktualnej
			}
		}
		///Wysylanie danych do LCD
		LCD_Clear();
		LCD_GoTo(0, 0);
		LCD_SendText(wynik);
		send_string(wynik);
		send_string("\r\n");
		///obliczanie i temperatury ustawionej
		LCD_GoTo(1, 0);
		LCD_SendText("Ust. Temp. ");
		LCD_GoTo(1, 12);
		if (ustaw >= 0) {
			ustaw1 = ustaw / 10;
			ustaw2 = ustaw % 10;
			if (ustaw1 > 9)
				sprintf(wynik2, "%d,%d", ustaw1, (uint16_t) ustaw2);///wyswietlanie temperatury ustawionej
			else
				sprintf(wynik2, " %d,%d", ustaw1, (uint16_t) ustaw2);///wyswietlanie temperatury ustawionej
			LCD_SendText((uint8_t*) wynik2);
		} else {
			///obliczanie i temperatury ustawionej
			ustaw1 = abs(ustaw) / 10;
			ustaw2 = abs(ustaw) % 10;
			if (ustaw1 >= 10)
				LCD_GoTo(1, 11);
			sprintf(wynik2, "-%d,%d", ustaw1, (uint16_t) ustaw2);//wyswietlanie temperatury ustawionej
			LCD_SendText((uint8_t*) wynik2);
		}

	}
	///Obliczanie temp ustawionej
	if (ustaw > 0) {	  			///jezeli temperatura dodatnia
		wartosc_ust = ustaw * 1.7;
		///Ustawienie histerezy nastaw
		if (ustaw > 250) {
			wartosc_ust = wartosc_ust + 5;
		} else {
			wartosc_ust = wartosc_ust - 5;
		}
		if (ustaw < 0)
			wartosc_ust = wartosc_ust - 5;

		wartosc_ust = wartosc_ust + 2108;
		odl = wartosc_ust - wartosc_akt;

	} else {///jesli temperatura ujemna
		wartosc_ust = (abs(ustaw) * 1.700);
		wartosc_ust = 2108 - wartosc_ust;
		odl = wartosc_ust - wartosc_akt;
	}
	///Przelaczanie peltiera grzanie/chlodzenie
	if (wartosc_ust < wartosc_akt) {
		GPIO_SetBits(GPIOC, GPIO_Pin_7);
	} else {
		GPIO_ResetBits(GPIOC, GPIO_Pin_7);
	}
///Obliczanie mocy dostarczanej do ogniwa

	if (abs(odl) > 70) {	  		///jezeli duza odleglosc do celu, pelna moc
		speed = 7000;
		if (ustaw < 100)
			speed = 10000;
	} else {	  			///jezeli blisko celu, wyrównuj stala calkowa
		if (abs(odl < 10)) {
			if (ustaw < 25) {
				calka = calka + odl * 0.01;
			} else {
				if (abs(odl) < 7) {
					calka = calka - odl * 0.01;
				}
			}
		}

/// obliczanie wspolczynnikow PID
		calka = calka + odl * 0.01;
		if (calka > 10000)
			calka = 10000;
		rozniczka = (odl - odl1) * 10;
		odl1 = odl;

		if (ustaw > 500) {
			speed = 85 * odl + 3 * calka + 20 * rozniczka; /// dla temp>50
		} else {
			if (ustaw >= 250) {
				speed = 85 * odl + 3 * calka + 20 * rozniczka; /// dla 50>temp>25
			} else {
				if (ustaw >= 150) {
					speed = 80 * odl + 2 * calka + 35 * rozniczka; /// dla 25>temp>15
				} else {
					if (ustaw > 10) {
						speed = 150 * odl + 3 * calka + 56 * rozniczka; /// dla 15>temp>10
					} else {
						if (ustaw > 0) {
							speed = 750 * odl + 10 * calka + 5 * rozniczka; /// dla 10>temp>0
						} else {
							speed = 1050 * odl + 40 * calka + 5 * rozniczka; /// dla temp<0
						}
					}
				}
			}
		}
	}
///podanie mocy na ogniwo
	speed = abs(speed);
	if (speed < 0)
		speed = 0;
	if (speed > 10000)
		speed = 10000;
	TIM_SetCompare1(TIM3, speed);

}

/******************************************************************************/
/*                 STM32F1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_md.s).                                            */
/******************************************************************************/

/**
 * @brief  This function handles PPP interrupt request.
 * @param  None
 * @retval None
 */

void USART1_IRQHandler(void) {

	if (USART_GetITStatus(USART1, USART_IT_RXNE)) {
		char c = USART_ReceiveData(USART1); ///pobierz komunikat
		switch (c) {
		case 'c':
			///odebrano c
			send_string("Odebrano komunikat c!\r\n");
			send_string("Zwiekszyc temperature o 1 stopien!\r\n");
			ustaw = ustaw + 10;
			break;
		case 'z':
			///odebrano z
			send_string("Odebrano komunikat z!\r\n");
			send_string("Zmniejszyc temperature o 1 stopien!\r\n");
			ustaw = ustaw - 10;
			break;
		default:
			///odebrano blad
			send_string("Nieznany komunikat:(\r\n");
			break;
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}

}

/************************************************
 * Przycisk zmniejszania temperatury ustawionej
 ***********************************************/
void EXTI1_IRQHandler() {
	if (EXTI_GetITStatus(EXTI_Line1)) {
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0) {
			/// jesli przycisk jest przycisniety
			///Ustawianie zmiennych i flag
			GPIO_SetBits(GPIOC, GPIO_Pin_9);
			ustpocz = ustaw;
			flaga = 1;
			ustaw--;
			///Obsluga USART
						send_string("zmniejsz obroty!\r\n");
						send_string("Ustawiona temperatura to :");
						sprintf(wynikel, "%d", ustaw);
						send_string(wynikel);
						send_string(" \r\n");
						send_string("Gotowy!\r\n");
			/// Decyzja czy przycisk jest wcisniety czy przyptrzymany
			for (czy = 0; czy < 400000; czy++)
				;
			while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0) {
				///Jesli przytrzymany, zatrzymaj prace programu i plynnie reguluj temperature
				TIM_Cmd(TIM3, DISABLE);
				ustaw = ustaw - 10;///<Wartosc kwantu zmiany
				/// Regulacja plynnosci
				for (czy = 0; czy < 241000; czy++)
					;
				///Wysylanie zmienianej temperatury ustawionej na LCD
				ustaw1 = ustaw / 10;
				ustaw2 = ustaw % 10;
				if (ustaw < 0) { //temperatury ujemne
					if (ustaw1 < -9) {
						LCD_GoTo(1, 10);
						sprintf(wynik2, " %d,%d", ustaw1, (uint16_t) ustaw2); //ustaw
					} else {
						LCD_GoTo(1, 10);
						sprintf(wynik2, "  %d,%d", ustaw1, (uint16_t) ustaw2); //ustaw
					}
				} else { //temperatury  dodatnie
					if (ustaw1 > 9) {
						LCD_GoTo(1, 10);
						sprintf(wynik2, "  %d,%d", ustaw1, (uint16_t) ustaw2); //ustaw
					} else {
						LCD_GoTo(1, 10);
						sprintf(wynik2, "   %d,%d", ustaw1, (uint16_t) ustaw2); //ustaw
					}

				}
				LCD_SendText((uint8_t*) wynik2); ///<Wyslij do LCD

			}
			///Obliczanie zmiany nastaw
			ustkon = ustaw;
			ustdelta = abs(ustkon - ustpocz);
			///Jesli zmiana jest duza, reset wspolczynnika calkowego aby zapobiec zbyt duzej wartosci
			if (ustdelta > 50)
				calka = 0;

			TIM_Cmd(TIM3, ENABLE);
		} else {
		}
///Zerowanie flagi przerwania
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

/************************************************
 * Przycisk zwiekszania temperatury ustawionej
 ***********************************************/
void EXTI2_IRQHandler() {
	if (EXTI_GetITStatus(EXTI_Line2)) {
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0) {
			/// jesli przycisk jest przycisniety

			///Ustawianie zmiennych i flag
			ustpocz = ustaw;
			ustaw++;
			GPIO_SetBits(GPIOC, GPIO_Pin_9);
			flaga = 0;
			///Obsluga USART
						send_string("wiecej obrotów!\r\n");
						send_string("Ustawiona temperatura to ");
						sprintf(wynikel, "%d", ustaw);
						send_string(wynikel);
						send_string(" \r\n");
						send_string("Gotowy!\r\n");
						/// Decyzja czy przycisk jest wcisniety czy przyptrzymany
			for (czy = 0; czy < 400000; czy++)
				;
			while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0) {
				///Jesli przytrzymany, zatrzymaj prace programu i plynnie reguluj temperature
				ustaw = ustaw + 10;///<Wartosc kwantu zmiany
				/// Regulacja plynnosci
				for (czy = 0; czy < 241000; czy++)
					;
				///Wysylanie zmienianej temperatury ustawionej na LCD
				ustaw1 = ustaw / 10;
				ustaw2 = ustaw % 10;

				if (ustaw < 0) { ///temperatury ujemne
					if (ustaw1 < -9) {
						LCD_GoTo(1, 10);
						sprintf(wynik2, " %d,%d", ustaw1, (uint16_t) ustaw2); //ustaw
					} else {
						LCD_GoTo(1, 10);
						sprintf(wynik2, "  %d,%d", ustaw1, (uint16_t) ustaw2); //ustaw
					}
				} else { /// temperatury dodatnie
					if (ustaw1 > 9) {
						LCD_GoTo(1, 10);
						sprintf(wynik2, "  %d,%d", ustaw1, (uint16_t) ustaw2); //ustaw
					} else {
						LCD_GoTo(1, 10);
						sprintf(wynik2, "   %d,%d", ustaw1, (uint16_t) ustaw2); //ustaw
					}

				}
				LCD_SendText((uint8_t*) wynik2);///<Wyslij do LCD
			}
			///Ograniczenie gorne nastaw = 90 stopni
			if (ustaw > 900)
				ustaw = 900;
			///Obliczanie zmiany nastaw
			ustkon = ustaw;
			ustdelta = abs(ustkon - ustpocz);
			///Jesli zmiana jest duza, reset wspolczynnika calkowego aby zapobiec zbyt duzej wartosci
			if (ustdelta > 50)
				calka = 0;
		} else {
		}
		///Zerowanie flagi przerwania
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

/*void PPP_IRQHandler(void)
 {
 }*/

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
