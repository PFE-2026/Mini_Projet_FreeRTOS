/*
 * uart.c
 *
 *  Created on: Feb 17, 2026
 *      Author: esaadi@actia.local
 */

#include "uart.h"

void uart_init()
{
	  huart2.Instance = USART2;
	  huart2.Init.BaudRate = 115200;
	  huart2.Init.WordLength = UART_WORDLENGTH_8B;
	  huart2.Init.StopBits = UART_STOPBITS_1;
	  huart2.Init.Parity = UART_PARITY_NONE;
	  huart2.Init.Mode = UART_MODE_TX_RX;
	  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	  if (HAL_UART_Init(&huart2) != HAL_OK)
	  {
	    Error_Handler();
	  }
	}
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(huart->Instance==USART2)
  {
    /* USER CODE BEGIN USART2_MspInit 0 */

    /* USER CODE END USART2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
    /* USER CODE BEGIN USART2_MspInit 1 */

    /* USER CODE END USART2_MspInit 1 */

  }

}
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance==USART2)
  {
    /* USER CODE BEGIN USART2_MspDeInit 0 */

    /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt DeInit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
    /* USER CODE BEGIN USART2_MspDeInit 1 */

    /* USER CODE END USART2_MspDeInit 1 */
  }

}

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
	command_handler_t user_command ;
	// Command cmd;
	signal_generator_handle_t signal = {0} ;
	Send_menu();
	while(1)
	{
		// xQueueReceive(q_command_choice, &cmd,portMAX_DELAY);
		xQueueReceive(q_command_choice, &user_command.cmd,portMAX_DELAY);

		// switch(cmd)
		switch (user_command.cmd)
		{
		case START:
			// start_pwm();
			signal_generator_start(&htim1,TIM_CHANNEL_1);
			// signal_generator(&htim1, TIM_CHANNEL_1);
			break;

		case STOP:
			// stop_pwm();
			signal_generator_stop (&htim1,TIM_CHANNEL_1);
			break;
		case SET_FREQ:
			// Set_Frequncy(uint32_t frequency);
			signal_generator_set_frequncy(signal.frequency);
			break;
		case SET_DUTY:
			signal_generator_set_duty_cycle(signal.duty);
			// Set_Duty(uint8_t duty
			break;
		case MEASURE:
			HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);   // main channel for Period
			HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_2);   // Indirect channel for Pulse
			break;
		}

	}
}
uint16_t Calculate_CRC(uint16_t cmd, uint16_t value)
{
    return (cmd + value) & 0xFFFF;
}
