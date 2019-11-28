/*
 * communication.c
 *
 *  Created on: Nov 28, 2019
 *      Author: benjamin
 */


#include "usart.h"
#include "gpio.h"
#include "communication.h"
#include "string.h"

ITStatus UartReady = RESET;
static uint8_t Buffer[] = "Hello World interrupt!";

void get_current_time(){
	if(HAL_UART_Transmit_IT(&huart5, (uint8_t*)Buffer, BUFFERSIZE) != HAL_OK){
		Error_Handler();
	}

	/*Wait for end of transfer*/
	while(UartReady != SET);

	/*Reset transmission flag*/
	UartReady = RESET;

}

void transmit(uint8_t* string){
	HAL_UART_Transmit(&huart5, (uint8_t*)string, strlen(string), 5000);
}

uint8_t * recieve(){
	static uint8_t buffer[BUFFERSIZE];

	HAL_UART_Receive(&huart5, (uint8_t*)buffer, BUFFERSIZE, 100000);

	return buffer;
}


/**
 * @brief Tx transfer completed callback
 * @param UartHandle: UART handle
 * @note This example shows a simple way to report end of IT Tx transfer, and
 * 		 you can add your own implementation.
 * @return None
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle){
	/* Set transmission flag: transfer complete */
	UartReady = SET;
}

/**
 * @brief Rx transfer completed callback
 * @param UartHandle: UART handle
 * @note This example shows a simple way to report end of IT Tx transfer, and
 * 		 you can add your own implementation.
 * @return None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * UartHandle){
	/* Set transmission flag: transfer complete */
	UartReady = SET;
}
