/*
 * tasks.h
 *
 *  Created on: Feb 23, 2026
 *      Author: esaadi@actia.local
 */

#ifndef INC_TASKS_H_
#define INC_TASKS_H_

#include "stm32f4xx_hal.h"

#include "main.h"
#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "Signal_Generation.h"

#include "Signal_Measurement.h"
#include "uart.h"

#include "main.h"
#include "uart.h"
void command_control(void *argument);

extern volatile uint8_t user_choice;

extern QueueHandle_t q_command_choice;
extern xTaskHandle handle_command_task;


#endif /* INC_TASKS_H_ */
