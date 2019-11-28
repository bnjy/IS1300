/*
 * backlight.c
 *
 *  Created on: Nov 27, 2019
 *      Author: benjamin
 */

#include <stdio.h>
#include <stdlib.h>
#include "adc.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "display.h"
#include "lcd.h"
#include "string.h"

/**
 @brief backlight_set, sets the lcd backlight to a specified color
 @param void
 */
void backlight_set(void){
	HAL_GPIO_WritePin(GPIOC, Disp_White_Pin, GPIO_PIN_SET);
}
