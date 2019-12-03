/*
 * communication.h
 *
 *  Created on: Nov 28, 2019
 *      Author: benjamin
 */

#ifndef INC_COMMUNICATION_H_
#define INC_COMMUNICATION_H_

#define BUFFERSIZE 10

#include <stdint.h>

void transmit(uint8_t* string);
uint8_t * recieve();

#endif /* INC_COMMUNICATION_H_ */
