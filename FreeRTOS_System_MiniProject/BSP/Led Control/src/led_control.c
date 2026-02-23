/*
 * led_control.c
 *
 *  Created on: Feb 18, 2026
 *      Author: esaadi@actia.local
 */
#include "led_control.h"

void GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */

	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_14, GPIO_PIN_RESET);

//	/*Configure GPIO pin : PA0 */
//	GPIO_InitStruct.Pin = GPIO_PIN_0;
//	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	 /*Configure GPIO pin : PA0 */
	  GPIO_InitStruct.Pin = GPIO_PIN_0;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(EXTI0_IRQn,7, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	/*Configure GPIO pins : PD12 PD14 */
	GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_14;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */
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
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uart_frame_t cmd ;
	// Command cmd;
	cmd.cmd= START ;
	xQueueSendFromISR(q_command_choice ,&cmd , NULL);

}

