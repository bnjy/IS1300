/**
 * @file backlight.c
 * @author Benjamin Roth
 * @date Nov 27, 2019
 * @brief Display backlight logic. In this file functions are declared to be able to set the display
 * background color and set the display contrast with timer PWM.
 */

#include "backlight.h"
#include "gpio.h"
#include "tim.h"
#include "adc.h"

/**
 * @brief backlight_set_brightness gets a value from function get_adc_value and sets the backlight brightness with that value.
 * uses PWM/TIM3 to be able to set the display brightness.
 * @param void
 * @return void
 */
void backlight_set_brightnes(void){
	uint32_t ADCval = get_adc_value();
	htim3.Instance->CCR2 = ADCval;
}

/**
 * @brief backlight_set_white sets the lcd backlight to white backlight color
 * @param void
 */
void backlight_set_white(void){
	HAL_GPIO_WritePin(GPIOC, Disp_White_Pin, GPIO_PIN_SET);
}

/**
 * @brief backlight_set_red sets the lcd backlight to red backlight color
 * @param void
 */
void backlight_set_red(void){
	HAL_GPIO_WritePin(GPIOC, Disp_Red_Pin, GPIO_PIN_SET);
}

/**
 * @brief backlight_set_green sets the lcd backlight to green backlight color
 * @param void
 */
void backlight_set_green(void){
	HAL_GPIO_WritePin(GPIOC, Disp_Green_Pin, GPIO_PIN_SET);
}
