/*
 * Pingpong.h
 *
 *  Created on: Nov 1, 2019
 *      Author: Benjamin Roth
 */

#ifndef INC_PINGPONG_H_
#define INC_PINGPONG_H_

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"

void Pingpong(void);
void Led_on(uint8_t Lednr);
void Blink_LEDs(void);
void Show_points(uint8_t L_points, uint8_t R_points);
bool L_hit(void);
bool L_hit(void);

#endif /* INC_PINGPONG_H_ */
