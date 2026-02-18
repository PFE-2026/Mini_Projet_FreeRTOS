/*
 * Signal_Generation.h
 *
 *  Created on: Feb 17, 2026
 *      Author: esaadi@actia.local
 */

#ifndef INC_SIGNAL_GENERATION_H_
#define INC_SIGNAL_GENERATION_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include <stdint.h>
#include "main.h"
#include "stm32f4xx_hal.h"


extern TIM_HandleTypeDef htim1;


typedef struct
{
	TIM_HandleTypeDef * signalGeneraterTimer;
	uint32_t frequency ;
	uint8_t duty;
}signal_generator_handle_t ;

uint8_t signal_generator_init ();
uint8_t signal_generator_deinit ();
uint8_t signal_generator_start ();
uint8_t signal_generator_stop ();

uint8_t signal_generator_set_frequncy(uint32_t frequency);
uint8_t signal_generator_set_duty_cycle(uint8_t duty);

#endif /* INC_SIGNAL_GENERATION_H_ */
