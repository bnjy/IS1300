/*
 * communication.c
 *
 *  Created on: Nov 28, 2019
 *      Author: benjamin
 */

#include "communication.h"
#include "usart.h"

ITStatus UartReady = RESET;

/**
 @brief transmit, takes a string pointer and transmits the string via HAL function HAL_UART_Transmit.
 @param string, a string pointer.
 @return void
 */
void transmit(uint8_t* string){
	HAL_UART_Transmit(&huart5, (uint8_t *)string, strlen(string), 5000);
}

/**
 @brief recieve, function that recieves input from user via UART USB. Uses HAL function HAL_UART_Receive with
 a maximum buffer size of BUFFERSIZE, which relates to the size of the lcd display.
 @param void
 @return buffer
 */
uint8_t * recieve(){
	static uint8_t buffer[BUFFERSIZE];

	HAL_UART_Receive(&huart5, (uint8_t *)buffer, sizeof(buffer), 50000);

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
