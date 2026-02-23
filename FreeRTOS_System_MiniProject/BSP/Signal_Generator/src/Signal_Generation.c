/*
 * Signal_Generation.c
 *
 *  Created on: Feb 17, 2026
 *      Author: esaadi@actia.local
 */

#include "Signal_Generation.h"



uint8_t signal_generator_init ()
{
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

	/* USER CODE BEGIN TIM1_Init 1 */

	/* USER CODE END TIM1_Init 1 */
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 15;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 999;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM1_Init 2 */

	/* USER CODE END TIM1_Init 2 */
	HAL_TIM_MspPostInit(&htim1);
	return 0;
}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(htim->Instance==TIM1)
	{
		/* USER CODE BEGIN TIM1_MspPostInit 0 */

		/* USER CODE END TIM1_MspPostInit 0 */

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**TIM1 GPIO Configuration
    PA8     ------> TIM1_CH1
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_8;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN TIM1_MspPostInit 1 */

		/* USER CODE END TIM1_MspPostInit 1 */
	}

}
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{
	if(htim_pwm->Instance==TIM1)
	{
		/* USER CODE BEGIN TIM1_MspInit 0 */

		/* USER CODE END TIM1_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_TIM1_CLK_ENABLE();
		/* USER CODE BEGIN TIM1_MspInit 1 */

		/* USER CODE END TIM1_MspInit 1 */

	}

}
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm)
{
	if(htim_pwm->Instance==TIM1)
	{
		/* USER CODE BEGIN TIM1_MspDeInit 0 */

		/* USER CODE END TIM1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM1_CLK_DISABLE();
		/* USER CODE BEGIN TIM1_MspDeInit 1 */

		/* USER CODE END TIM1_MspDeInit 1 */
	}

}
uint8_t signal_generator_set_frequncy(uint32_t frequency)
{
	uint32_t APB1_FREQ=16000000;
	uint32_t PSC = 15;
	uint32_t ARR ;
	ARR =(APB1_FREQ/((1+PSC)*frequency) -1);
	__HAL_TIM_SET_AUTORELOAD(&htim1, ARR);
	__HAL_TIM_SET_COUNTER(&htim1,0);
	return 0 ;
}

uint8_t signal_generator_set_duty_cycle(uint8_t duty)
{
	uint32_t ARR = __HAL_TIM_GET_AUTORELOAD(&htim1);
	uint32_t CCR ;
	CCR = (duty*(ARR+1))/ 100 ;
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,CCR);
	return 0;
}


uint8_t signal_generator_start (TIM_HandleTypeDef *htim, uint32_t Channel)
{
	HAL_TIM_PWM_Start(htim, Channel);
	__HAL_TIM_MOE_ENABLE(&htim1);
	return 0;
}

uint8_t signal_generator_stop (TIM_HandleTypeDef *htim, uint32_t Channel)
{
	HAL_TIM_PWM_Stop(htim, Channel);
	return 0;
}

/*
void Set_Frequncy(uint32_t frequency)
{
	uint32_t APB1_FREQ=16000000;
	uint32_t PSC = 15;
	uint32_t ARR ;
	ARR =(APB1_FREQ/((1+PSC)*frequency) -1);
	__HAL_TIM_SET_AUTORELOAD(&htim1, ARR);
	__HAL_TIM_SET_COUNTER(&htim1,0);
}

void Set_Duty(uint8_t duty)
{
	uint32_t ARR = __HAL_TIM_GET_AUTORELOAD(&htim1);
	uint32_t CCR ;
	CCR = (duty*(ARR+1))/ 100 ;
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,CCR);
}
 */
/*
void start_pwm()
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

void stop_pwm()
{
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}
 */
