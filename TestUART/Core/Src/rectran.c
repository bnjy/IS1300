/*
 * rectran.c
 *
 *  Created on: Nov 11, 2019
 *      Author: benja
 */

#include "usart.h"
#include "gpio.h"
#include "rectran.h"

#define BUFFERSIZE 22

ITStatus UartReady = RESET;
static uint8_t Buffer[] = "Hello World interrupt!";

void RunTransmit(void){
	  if(HAL_UART_Transmit_IT(&huart5, (uint8_t*)Buffer, BUFFERSIZE) != HAL_OK){
		  Error_Handler();
	  }
}

void RunReceive(void){

	uint8_t i = 0;
	while (i < BUFFERSIZE){
	  if(HAL_UART_Receive_IT(&huart5, (uint8_t*)Buffer, BUFFERSIZE) != HAL_OK){
		  Error_Handler();
	  }
	  i++;
	}

	  /*Wait for end of transfer*/
	  while(UartReady != SET){
		  RunTransmit();
	  }

	  /*Reset transmission flag*/
	  UartReady = RESET;
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

