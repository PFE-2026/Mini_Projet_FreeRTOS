/*
 * uart.c
 *
 *  Created on: Feb 17, 2026
 *      Author: esaadi@actia.local
 */

// #include "main.h"
/*#include <string.h>
#include <stdio.h>
#include "Signal_Generation.h"*/


#include "uart.h"

void Send_menu(void){
	const char* msg_menu =
			"|         Menu         |\n\r"
			"========================\n"
			"1. Start PWM \n\r"
			"2. Stop PwM \n\r"
			"3.	Set Frequency\r\n"
			"4.	Set Duty Cycle\r\n"
			"5.	Measure Frequency\r\n"
			"Enter your choice here : ";

	while (1)
	{
		// HAL_UART_Transmit_IT(&huart2, (uint8_t*)msg_menu, strlen(msg_menu));
		HAL_UART_Transmit (&huart2, (uint8_t*)msg_menu, strlen(msg_menu),HAL_MAX_DELAY);
	}
}


void command_control(void *argument)
{
	Command cmd;

	Send_menu();
	while(1)
	{
		xQueueReceive(q_command_choice, &cmd,portMAX_DELAY);
		switch (cmd)
		{
		case START:
			// start_pwm();
			break;

		case STOP:
			// stop_pwm();
			break;

		case SET_FREQ:
			// Set_Frequncy(uint32_t frequency);
			break;
		case SET_DUTY:
			// Set_Duty(uint8_t duty
			break;
		case MEASURE:
			HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);   // main channel for periode
			HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_2);   // indirect channel for pulse
			break;

		}



	}
}
