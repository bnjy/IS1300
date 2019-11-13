/*
 * rectran.h
 *
 *  Created on: Nov 11, 2019
 *      Author: benja
 */

#ifndef INC_RECTRAN_H_
#define INC_RECTRAN_H_

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle);
void RunReceive(void);
void RunTransmit(void);

#endif /* INC_RECTRAN_H_ */
