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

extern void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
extern void measure_task(void *argument);
extern  QueueHandle_t q_led_control;


typedef struct
{
	float Frequency ;
	float duty ;
}signal_measure_t ;


#endif /* INC_SIGNAL_MEASUREMENT_H_ */
