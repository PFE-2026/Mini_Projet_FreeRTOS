/*
 * uart.h
 *
 *  Created on: Feb 17, 2026
 *      Author: esaadi@actia.local
 */

#ifndef UART_UART_H_
#define UART_UART_H_
#include "main.h"
#include <string.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "Signal_Generation.h"
#include "Signal_Measurement.h"

#define MAX_PAYLOAD_LEN 128U
typedef enum
{
	START=0, // 0
	STOP,
	SET_FREQ,
	SET_DUTY,
	MEASURE
}uart_cmd_t  ;

typedef struct
{
	uart_cmd_t cmd;
	uint16_t length;
	uint8_t payload[MAX_PAYLOAD_LEN ];
	uint32_t crc ;
}uart_frame_t;

void uart_init();
// void Send_menu(void);
void command_control(void *argument);
void HAL_UART_MspInit(UART_HandleTypeDef* huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart);
// uint16_t Calculate_CRC(uint16_t cmd, uint16_t value) ;
uint32_t Calculate_Frame_Checksum(uart_frame_t *frame);



// Typdef Handlers
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

extern volatile uint8_t user_choice;

extern QueueHandle_t q_command_choice;
extern xTaskHandle handle_command_task;



#endif /* UART_UART_H_ */
