/**
 * @file communication.h
 * @author Benjamin Roth
 * @date Nov 27, 2019
 * @brief header file to communication.c
 */

#ifndef INC_COMMUNICATION_H_
#define INC_COMMUNICATION_H_

#define BUFFERSIZE 10

#include <stdint.h>

void transmit(uint8_t* string);
uint8_t * recieve();

#endif /* INC_COMMUNICATION_H_ */
