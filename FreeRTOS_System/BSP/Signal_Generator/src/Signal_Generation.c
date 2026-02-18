/*
 * Signal_Generation.c
 *
 *  Created on: Feb 17, 2026
 *      Author: esaadi@actia.local
 */



#include "Signal_Generation.h"


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

uint8_t signal_generator_start (TIM_HandleTypeDef *htim, uint32_t Channel)
{
	HAL_TIM_PWM_Start(htim, Channel);
	return 0;
}

uint8_t signal_generator_stop (TIM_HandleTypeDef *htim, uint32_t Channel)
{
	HAL_TIM_PWM_Start(htim, Channel);
return 0;
	}

void start_pwm()
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

void stop_pwm()
{
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}
