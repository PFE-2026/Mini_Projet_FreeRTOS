/*
 * Signal_Measurement.c
 *
 *  Created on: Feb 17, 2026
 *      Author: esaadi@actia.local
 */

#include "main.h"

#include "Signal_Measurement.h"

uint8_t signal_measure_init ()
{
	TIM_SlaveConfigTypeDef sSlaveConfig = {0};
	TIM_IC_InitTypeDef sConfigIC = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 0;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 4294967295;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
	sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
	sSlaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
	sSlaveConfig.TriggerPrescaler = TIM_ICPSC_DIV1;
	sSlaveConfig.TriggerFilter = 0;
	if (HAL_TIM_SlaveConfigSynchro(&htim2, &sSlaveConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
	sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	sConfigIC.ICFilter = 0;
	if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
	sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
	if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	return 0;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	signal_measure_t signal_measure=  {0};
	BaseType_t task_prioriy_high = 0;


	if ( (htim->Instance == TIM2) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1))
	{
		uint32_t period = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		uint32_t high_pulse = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);

		if (period != 0)
		{
			signal_measure.Frequency = (float)Timer_clock / (float) period ;
			signal_measure.duty = ((float)high_pulse/period)*100.0f; // (high/T )*100
		}
		/*
		 * * @param pxHigherPriorityTaskWoken xQueueGenericSendFromISR() will set
		 * *pxHigherPriorityTaskWoken to pdTRUE if sending to the queue caused a task
		 * to unblock, and the unblocked task has a priority higher than the currently running task.
		 * If xQueueGenericSendFromISR() sets this value to pdTRUE then a context switch should be requested
		 * before the interrupt is exited.
		 */
		xQueueSendFromISR (q_led_control , &signal_measure  , &task_prioriy_high); // Task plus Prioritaire entre en running state ?
		xQueueSendFromISR (q_measure, &signal_measure  , &task_prioriy_high); // Task plus Prioritaire entre en running state ?

		if  ( task_prioriy_high == 1 )
		{
			/*TODO */
			task_prioriy_high = pdTRUE; // Tache plus prioritaire ==> we can do Switch conntext
		}
		else
		{
			/* We have not woken a task at the start of the ISR.
			 *  xHigherPriorityTaskWokenByPost = pdFALSE;*/
			task_prioriy_high =  pdFALSE;
		}
		/* Now the buffer is empty we can switch context if necessary.  Note that the
		 *  // name of the yield function required is port specific.
		 *  if( xHigherPriorityTaskWokenByPost )
		 *  {
		 *      portYIELD_FROM_ISR();
		 *  }
		 * */
		portYIELD_FROM_ISR(task_prioriy_high); // Pour pouvoir effectuer un switch in case another ask that have higher priority
	}
}
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef* htim_ic)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(htim_ic->Instance==TIM2)
	{
		/* USER CODE BEGIN TIM2_MspInit 0 */

		/* USER CODE END TIM2_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_TIM2_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**TIM2 GPIO Configuration
    PA5     ------> TIM2_CH1
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_5;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* TIM2 interrupt Init */
		HAL_NVIC_SetPriority(TIM2_IRQn, 7, 0);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);


		/* USER CODE BEGIN TIM2_MspInit 1 */

		/* USER CODE END TIM2_MspInit 1 */

	}
}
// Add signal Measure Start&Stop
uint8_t signal_measure_start ()
{
	TIM_HandleTypeDef *htim = &htim2;
	uint32_t Channel = TIM_CHANNEL_1 ;
	HAL_TIM_IC_Start_IT(htim, Channel);   // main channel for Period
	HAL_TIM_IC_Start(htim, Channel);   // Indirect channel for Pulse
	return 0;
}

uint8_t signal_Measure_stop ()
{
	TIM_HandleTypeDef *htim = &htim2;
	uint32_t Channel = TIM_CHANNEL_1 ;

	HAL_TIM_IC_Stop_IT(htim, Channel);
	HAL_TIM_IC_Stop(htim,Channel);
	return 0;

}

void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef* htim_ic)
{
	if(htim_ic->Instance==TIM2)
	{
		/* USER CODE BEGIN TIM2_MspDeInit 0 */

		/* USER CODE END TIM2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM2_CLK_DISABLE();

		/**TIM2 GPIO Configuration
    PA5     ------> TIM2_CH1
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5);

		/* TIM2 interrupt DeInit */
		HAL_NVIC_DisableIRQ(TIM2_IRQn);
		/* USER CODE BEGIN TIM2_MspDeInit 1 */

		/* USER CODE END TIM2_MspDeInit 1 */
	}

}

//// 1. Semaphore Entre Mesure et Afichage
//// 2. queue Entre MESURE ET LEDs Task et queue entre Mesure et affichage task (UART)
//
//void measure_task(void *argument)
//{
//		for(;;)
//		{
//
//			/* check flag CCx*/
//			/* get CCR1 & CCR2 value*/
//			/* calculate duty cycle and frequency*/
//
//			/* tasl sleep*/
//			vTaskDelay(1u);
//		}
//}
