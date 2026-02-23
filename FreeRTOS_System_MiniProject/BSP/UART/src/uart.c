/*
 * uart.c
 *
 *  Created on: Feb 17, 2026
 *      Author: esaadi@actia.local
 */

#include "uart.h"

void uart_init()
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}

	// __HAL_UART_ENABLE_IT(&huart2, UART_IT_ERR);
}
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(huart->Instance==USART2)
	{
		/* USER CODE BEGIN USART2_MspInit 0 */

		/* USER CODE END USART2_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_USART2_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USART2 interrupt Init */
		HAL_NVIC_SetPriority(USART2_IRQn, 6, 0);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
		/* USER CODE BEGIN USART2_MspInit 1 */

		/* USER CODE END USART2_MspInit 1 */

	}

}
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
	if(huart->Instance==USART2)
	{
		/* USER CODE BEGIN USART2_MspDeInit 0 */

		/* USER CODE END USART2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART2_CLK_DISABLE();

		/**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

		/* USART2 interrupt DeInit */
		HAL_NVIC_DisableIRQ(USART2_IRQn);
		/* USER CODE BEGIN USART2_MspDeInit 1 */

		/* USER CODE END USART2_MspDeInit 1 */
	}

}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    static uart_frame_t command;
    static uint16_t i = 0;
    static uint16_t payload_index = 0;
    static uint16_t length = 0;
    static uint8_t crc[4];
    static uint8_t crc_index = 0;

    //	crc = Calculate_Frame_Checksum(&command);
    //	/* Mecanisme pour extraire chaque partie reçue == l'alignée avec la la partie coresspendante
    //
    //	 * cmd	--> FIRST 2BYTES
    //	 * LENGTH 	--> SECOND 2BYTES
    //	 * payload 	--> 3 third part  peut aller jusqu'a 128 MAX valeurs de uint8_t
    //	 * CRC -->   4 PART SUR 32 BITS UINT32_T CALCULER A PARTIR DES AUTRES CHAMPS
    //
    //	 */
    //	// placer le byte obtenu par user dans un Tableau
    //	user_choice= rx_buffer[0];

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint8_t byte = user_choice;
    if(i == 0)
    {
        command.cmd = byte; // lsb
        i++;
    }
    else if(i == 1)
    {
        command.cmd |= ((uint16_t)byte << 8); //msb
        i++;
    }
else if(i == 2)
    {
        command.length = byte;
        i++;
    }
 else if(i == 3)
    {
command.length |= ((uint16_t)byte << 8);
  length = command.length;
   if(length > sizeof(command.payload)) // on peut pas dépasser  MAX_PAYLOAD_LEN
        {
     i = 0;
  HAL_UART_Receive_IT(huart, (uint8_t*)&user_choice, 1);
   return;
        }

 payload_index = 0;
        crc_index = 0;
        i++;
    }
 else if(payload_index < length) // sinon on stocke payload values
    {
        command.payload[payload_index++] = byte;

        if(payload_index == length)
        {
            i++;   // on revient  au CRC
        }
    }
    else if(crc_index < 4) // on recupere crc values
    {
        crc[crc_index++] = byte;

        if(crc_index == 4)
        {
            command.crc =  crc[0] | (crc[1] << 8) | (crc[2] << 16) | (crc[3] << 24); // reconstitution de msb---lsb

            uint32_t calculated_crc = Calculate_Frame_Checksum(&command);

            if(calculated_crc == command.crc)
            {
                xQueueSendFromISR(q_command_choice, &command,  &xHigherPriorityTaskWoken);
            }
            i = 0;
            payload_index = 0;
            crc_index = 0;
            length = 0;
        }
    }

    HAL_UART_Receive_IT(huart, (uint8_t*)&user_choice, 1);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
void command_control(void *argument)
{
	uart_frame_t user_command ;
	signal_measure_t measured_signal;
	// Send_menu();
	while(1)
	{
		//	xQueueReceive(q_command_choice, &user_command.cmd,portMAX_DELAY);
		xQueueReceive(q_command_choice, &user_command, portMAX_DELAY);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
		// switch(cmd)
		switch (user_command.cmd)
		{
		case START:
			// start_pwm();
			signal_generator_set_duty_cycle(50);
			signal_generator_set_frequncy(1000);
			signal_generator_start(&htim1,TIM_CHANNEL_1);
			break;

		case STOP:
			// stop_pwm();
			signal_generator_stop (&htim1,TIM_CHANNEL_1);
			break;
			/*	case SET_FREQ:
			// Set_Frequncy(uint32_t frequency);
			signal_generator_set_frequncy(signal.frequency);
			break;
		case SET_DUTY:
			signal_generator_set_duty_cycle(signal.duty);
			// Set_Duty(uint8_t duty*/
			//		case SET_FREQ:
			//			if(user_command.length >= 1)
			//				signal_generator_set_frequncy(user_command.payload[0]);
			//			break;
		case SET_FREQ:
			if(user_command.length >= 2) // On attend 2 octets
			{
				uint32_t freq = (uint32_t)user_command.payload[0] | ((uint32_t)user_command.payload[1] << 8);
				signal_generator_set_frequncy(freq);
			}
			break;
		case SET_DUTY:
			if(user_command.length >= 1)
				signal_generator_set_duty_cycle(user_command.payload[0]);
			break;
		case MEASURE:
			HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);   // main channel for Period
			HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_2);   // Indirect channel for Pulse (duty)

			if(xQueueReceive(q_measure, &measured_signal, pdMS_TO_TICKS(100)) == pdPASS)
			{
				char msg_buffer[64];
				int len = snprintf(msg_buffer, sizeof(msg_buffer),"Freq: %.2f Hz, Duty: %.2f %%\r\n",measured_signal.Frequency,measured_signal.duty);
				HAL_UART_Transmit(&huart2, (uint8_t*)msg_buffer, len, HAL_MAX_DELAY);
			}

			break;
		}

	}
}
uint32_t Calculate_Frame_Checksum(uart_frame_t *frame)
{
	uint32_t checksum = 0;

	checksum += frame->cmd;
	checksum += frame->length;
	for (uint16_t i = 0; i < frame->length; i++)
	{
		checksum += frame->payload[i];
	}

	return checksum;
}

/* void Send_menu(void)
{
	const char* msg_menu =
			"|         Menu         |\n\r"
			"========================\n"
			"1. Start PWM \n\r"
			"2. Stop PwM \n\r"
			"3.	Set Frequency\r\n"
			"4.	Set Duty Cycle\r\n"
			"5.	Measure Frequency\r\n"
			"Enter your choice here : ";

	while (1)
	{
		// HAL_UART_Transmit_IT(&huart2, (uint8_t*)msg_menu, strlen(msg_menu));
		HAL_UART_Transmit (&huart2, (uint8_t*)msg_menu, strlen(msg_menu),HAL_MAX_DELAY);
	}
}*/

//uint16_t Calculate_CRC(uint16_t cmd, uint16_t length , uint8_t pyload_val)
//{
//	return (cmd + value) & 0xFFFF;
//}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

}
