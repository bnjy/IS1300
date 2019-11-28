/*
 * test.c
 *
 *  Created on: 23 Nov 2019
 *      Author: benjamin
 */

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "display.h"
#include "lcd.h"
#include "backlight.h"
#include "test.h"


/**
 *
 */
void test_program(void){
	test_backlight_color();
	test_lcd_initialize();
	test_lcd_rom();
	test_lcd_clear();
	test_write_string();
	HAL_Delay(2000);
//	test_screen_colors();
}

void test_write_string(void){
	lcd_write_string("Zup");
}


/**
@brief test_write_char, a test to write a char to the display.
@param void
*/
void test_write_char(void){
	lcd_send_inst(0x80);

	lcd_send_data(0x77);
	lcd_send_data(0x61);
	lcd_send_data(0x64);
	lcd_send_data(0x64);
	lcd_send_data(0x61);
	lcd_send_data(0x70);
	lcd_send_data(0x3F);
}

/**
 *
 */
void test_backlight_color(void){
	backlight_set();
}

/**
 @brief test_display_initialize, a test to initialize the display
 @param void
 */
void test_lcd_initialize(void){
	lcd_initialize();
}
/**
 *
 */
void test_lcd_rom(void){
	lcd_setROM();
}

/**
 *
 */
void test_lcd_clear(void){
	lcd_clear();
}

/**
@brief test_screen_colors, the screen blinkes in three colors green, white and red.
@param void
*/
void test_screen_colors(void){
	HAL_GPIO_WritePin(GPIOC, Disp_Green_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOC, Disp_Green_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, Disp_White_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(GPIOC, Disp_White_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, Disp_Red_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(GPIOC, Disp_Red_Pin, GPIO_PIN_RESET);
}


