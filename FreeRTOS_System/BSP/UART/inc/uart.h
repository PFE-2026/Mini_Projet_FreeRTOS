/*
 * uart.h
 *
 *  Created on: Feb 17, 2026
 *      Author: esaadi@actia.local
 */

#ifndef UART_UART_H_
#define UART_UART_H_

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "stm32f4xx_hal.h"

#include "main.h"
#include <string.h>
#include <stdio.h>
#include "Signal_Generation.h"

void Send_menu(void);
void command_control(void *argument);


extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern volatile uint8_t user_choice;
extern QueueHandle_t q_command_choice;
extern xTaskHandle handle_command_task;


typedef enum
{
	START, // 0
	STOP,
	SET_FREQ,
	SET_DUTY,
	MEASURE
}Command ;

#endif /* UART_UART_H_ */
