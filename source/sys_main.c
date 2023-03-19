/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */

#include "system.h"
#include "rti.h"
#include "gio.h"

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

uint8_t period_state = 0; // переменная для контроля режима

uint32_t period_on; // переменная для установки времени включения
uint32_t period_off; // переменная для установки времени отключения

bool buttom_pressed = false; // флаг нажатия кнопки 123


void delay(uint32_t time) // простейшая программная задержка в блокирующем режиме
						  // ей в первый раз моргал светодиодом
{
    while (time>0) time--;
}

void period_changer(void) // процедура смены режима моргания
{

	period_state++;
	if (period_state == 4) period_state = 1; // сброс режима для цикличности

	switch (period_state) // сравнение для выбора времени исходя из номера режима
	{
		case 1:
			period_on =  500000U; // 500 мс при частоте таймера 1 МГц
			period_off = 500000U; // 500 мс при частоте таймера 1 МГц
			break;
		case 2:
			period_on =  250000U; // 250 мс при частоте таймера 1 МГц
			period_off = 250000U; // 250 мс при частоте таймера 1 МГц
			break;
		case 3:
			period_on =  100000U; // 100 мс при частоте таймера 1 МГц
			period_off = 900000U; // 900 мс при частоте таймера 1 МГц
			break;
	}

	rtiStopCounter(rtiCOUNTER_BLOCK0); // остановка таймера
	rtiResetCounter(rtiCOUNTER_BLOCK0); // сброс

	rtiREG1->CMP[0U].COMPx = period_on; // установка начального значения прямо в регистр
	rtiREG1->CMP[1U].COMPx = period_on + period_off;

	/* т.к. rtiSetPeriod меняет значение, которое прибавляется к компаратору, таймер
	 * сбрасывается и изменяется так же начальное значение */

	rtiSetPeriod(rtiCOMPARE0, period_on + period_off); //
	rtiSetPeriod(rtiCOMPARE1, period_on + period_off); //

	gioSetBit(gioPORTA, 2, 1); // включение диода

	rtiStartCounter(rtiCOUNTER_BLOCK0); // запуск таймера
}



/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */

	systemInit();
	gioInit();
	rtiInit(); // инициализация (все через HalCoGen)
	_enable_IRQ(); // разрешение прерывания

	rtiEnableNotification(rtiNOTIFICATION_COMPARE0); // разрешение прерывания для первого компаратора
	rtiEnableNotification(rtiNOTIFICATION_COMPARE1); // для второго компаратора

	gioEnableNotification(gioPORTA, 7); // разрешение прерывания кнопки

while(1)
{
	if (buttom_pressed == true)
	{
		buttom_pressed = false; // флаг нажатия кнопки
		period_changer();	// процедура смены режима
		delay(500000);		// задержка для устранения дребезка
		gioEnableNotification(gioPORTA, 7);		// разрешение прерываний для последующего срабатывания кнопки
	}	// т.к. задание только поморгать дидом, задержа тут, а не в процедуре смены режима
}

/* USER CODE END */


}


/* USER CODE BEGIN (4) */

void rtiNotification(uint32_t Notification) // обработчик прерывания таймера
{
	switch (Notification) // сравнение для определения, какой компаратор вызвал прерывание
	{
		case 1U:
			gioSetBit(gioPORTA, 2, 0);
			break;
		case 2U:
			gioSetBit(gioPORTA, 2, 1);
			break;
	}
}

void gioNotification(gioPORT_t *port, uint32 bit) // обработчик прерывания кнопки
{

	gioDisableNotification(gioPORTA, 7);	// запрет прерывания кнопки что бы дребезг контактов
											// не вызвал огромное количество прерываний
	buttom_pressed = true;					// флаг нажатия кнопки

}

/* USER CODE END */
