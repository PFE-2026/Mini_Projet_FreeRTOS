/*
 * tasks.c
 *
 *  Created on: Feb 23, 2026
 *      Author: esaadi@actia.local
 */

#include"tasks.h"
void command_control(void *argument)
{
	uart_frame_t user_command ;
	signal_measure_t measured_signal;
	// Send_menu();
	while(1)
	{
		//	xQueueReceive(q_command_choice, &user_command.cmd,portMAX_DELAY);
		xQueueReceive(q_command_choice, &user_command, portMAX_DELAY);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
		// switch(cmd)
		switch (user_command.cmd)
		{
		case START:
			// start_pwm();
			signal_generator_set_duty_cycle(50);
			signal_generator_set_frequncy(1000);
			signal_generator_start(&htim1,TIM_CHANNEL_1);
			break;

		case STOP:
			// stop_pwm();
			signal_generator_stop (&htim1,TIM_CHANNEL_1);
			break;
			/*	case SET_FREQ:
			// Set_Frequncy(uint32_t frequency);
			signal_generator_set_frequncy(signal.frequency);
			break;
		case SET_DUTY:
			signal_generator_set_duty_cycle(signal.duty);
			// Set_Duty(uint8_t duty*/
			//		case SET_FREQ:
			//			if(user_command.length >= 1)
			//				signal_generator_set_frequncy(user_command.payload[0]);
			//			break;
		case SET_FREQ:
			if(user_command.length >= 2) // On attend 2 octets
			{
				uint32_t freq = (uint32_t)user_command.payload[0] | ((uint32_t)user_command.payload[1] << 8);
				signal_generator_set_frequncy(freq);
			}
			break;
		case SET_DUTY:
			if(user_command.length >= 1)
				signal_generator_set_duty_cycle(user_command.payload[0]);
			break;
		case MEASURE:
			HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);   // main channel for Period
			HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_2);   // Indirect channel for Pulse (duty)

			if(xQueueReceive(q_measure, &measured_signal, pdMS_TO_TICKS(100)) == pdPASS)
			{
				char msg_buffer[64];
				int len = snprintf(msg_buffer, sizeof(msg_buffer),"Freq: %.2f Hz, Duty: %.2f %%\r\n",measured_signal.Frequency,measured_signal.duty);
				HAL_UART_Transmit(&huart2, (uint8_t*)msg_buffer, len, HAL_MAX_DELAY);
			}

			break;
		}

	}
}

void led_control(void *argument)
{
	for(;;)
	{
		signal_measure_t measure;
		xQueueReceive(q_led_control, &measure, portMAX_DELAY);
		if((measure.Frequency > 0 ) &&(measure.Frequency <= 10000))
		{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);


		}
		else if (measure.Frequency > 10000)
		{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_14, GPIO_PIN_RESET);

		}
	}
}
