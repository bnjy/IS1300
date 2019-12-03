/*
 * backlight.c
 *
 *  	Created on: Nov 27, 2019
 *      Author: Benjamin Roth
 *      Brief: Display backlight logic. In this file functions are declared to be able to set the display
 *      background color and set the display contrast with timer PWM.
 *
 */

#include "backlight.h"
#include "gpio.h"

/**
 @brief backlight_set_white, sets the lcd backlight to white backlight color
 @param void
 */
void backlight_set_white(void){
	HAL_GPIO_WritePin(GPIOC, Disp_White_Pin, GPIO_PIN_SET);
}

/**
 @brief backlight_set_red, sets the lcd backlight to red backlight color
 @param void
 */
void backlight_set_red(void){
	HAL_GPIO_WritePin(GPIOC, Disp_Red_Pin, GPIO_PIN_SET);
}

/**
 @brief backlight_set_green, sets the lcd backlight to green backlight color
 @param void
 */
void backlight_set_green(void){
	HAL_GPIO_WritePin(GPIOC, Disp_Green_Pin, GPIO_PIN_SET);
}
