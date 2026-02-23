/*
 * led_control.h
 *
 *  Created on: Feb 18, 2026
 *      Author: esaadi@actia.local
 */

#ifndef LED_CONTROL_INC_LED_CONTROL_H_
#define LED_CONTROL_INC_LED_CONTROL_H_

#include "main.h"
#include "uart.h"
#include "Signal_Measurement.h"

extern QueueHandle_t q_command_choice;



void led_control(void *argument);
void GPIO_Init(void);


#endif /* LED_CONTROL_INC_LED_CONTROL_H_ */
