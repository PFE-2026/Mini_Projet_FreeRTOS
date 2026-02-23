/*
 * Signal_Measurement.h
 *
 *  Created on: Feb 17, 2026
 *      Author: esaadi@actia.local
 */

#ifndef INC_SIGNAL_MEASUREMENT_H_
#define INC_SIGNAL_MEASUREMENT_H_
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "stm32f4xx_hal.h"

# define Timer_clock		8000000u

uint8_t signal_measure_init ();
extern void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef* htim_ic);
void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef* htim_ic);
uint8_t signal_measure_start ();
uint8_t signal_Measure_stop ();

extern QueueHandle_t q_led_control;
extern  QueueHandle_t q_measure;
extern TIM_HandleTypeDef htim2;


typedef struct
{
	float Frequency ;
	float duty ;
}signal_measure_t ;


#endif /* INC_SIGNAL_MEASUREMENT_H_ */
