/*
 * Signal_Measurement.c
 *
 *  Created on: Feb 17, 2026
 *      Author: esaadi@actia.local
 */

#include "main.h"

#include "Signal_Measurement.h"


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	signal_measure_t signal_measure=  {0};

	if ( (htim->Instance == TIM2) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1))
	{
		uint32_t period = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		uint32_t high_pulse = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);

		if (period != 0)
		{
			signal_measure.Frequency = (float)Timer_clock / (float) period ;
			signal_measure.duty = ((float)high_pulse/period)*100.0f; // (high/T )*100
		}
	}
	/*Set Queue */
	BaseType_t task_prioriy_high = 0;
	xQueueSendFromISR (q_led_control , &signal_measure  , &task_prioriy_high);
	if  ( task_prioriy_high == 1 )
	{
		/*TODO */
	}
	else
	{

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
