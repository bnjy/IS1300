/*
 * lcd.c
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
#include "backlight.h"
#include "string.h"

uint8_t start = 0;
uint8_t first = 0;
uint8_t second = 0;
uint8_t buffer[3];

/**
 @brief lcd_send_data, setup of display bitstream for data, with RS and RW variable set to 0.
 	 	 	 	 	   SID Input bitstream to be set: 1111 10(RW)0(RS)0 D0D1D2D3 0000 D4D5D6D7 0000
 @param inst, instruction to be sent to the display
 */
void lcd_send_inst(uint8_t inst){
	uint8_t startByte = 0x1F; 		//Send 5 synchronisation bits, RS = 0, R/W = 0. Byte(LSB): 1111 1000
	uint8_t firstByte = 0x00;		//Byte(LSB): 0000 0000
	uint8_t secondByte = 0x00;		//Byte(LSB): 0000 0000

	firstByte = firstByte | (inst & 0x0F);	//firstByte: D0D1D2D3 0000

	secondByte = (inst >> 4) & 0x0F;

	buffer[0] = startByte;
	buffer[1] = firstByte;
	buffer[2] = secondByte;

	HAL_GPIO_WritePin(GPIOB, Disp_PB12_Pin, GPIO_PIN_RESET);
	HAL_Delay(5);
	HAL_SPI_Transmit(&hspi2, buffer, 3, 1000);
	HAL_GPIO_WritePin(GPIOB, Disp_PB12_Pin, GPIO_PIN_SET);
}
/**
 @brief lcd_send_data, setup of display bitstream for data, with RS variable set to 1.
 	 	 	 	 	   SID Input bitstream to be set: 1111 10(RW)1(RS)0 D0D1D2D3 0000 D4D5D6D7 0000
 @param data, data byte to be sent to the display
 @return void
 */
void lcd_send_data(uint8_t data){
	uint8_t startByte = 0x5F; 		//Send 5 synchronisation bits, RS = 1, R/W = 0. Byte(LSB): 1111 1010
	uint8_t firstByte = 0x00;		//Byte(LSB): 0000 0000
	uint8_t secondByte = 0x00;		//Byte(LSB): 0000 0000

	firstByte = firstByte | (data & 0x0F);

	secondByte = (data >> 4) & 0x0F;

	buffer[0] = startByte;
	buffer[1] = firstByte;
	buffer[2] = secondByte;

	HAL_GPIO_WritePin(GPIOB, Disp_PB12_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, buffer, 3, 1000);
	HAL_GPIO_WritePin(GPIOB, Disp_PB12_Pin, GPIO_PIN_SET);
}

/**
 @brief display_initialize, display initialisation according to the example in display data sheet.
 @param void
 @return void
 */
void lcd_initialize(void){
	lcd_send_inst(FUNCTION_SET_1);
	lcd_send_inst(EXTENDED_FUNCTION_SET);
	lcd_send_inst(ENTRY_MODE_SET);
	lcd_send_inst(BIAS_SETTING);
	lcd_send_inst(FUNCTION_SET_2);
	lcd_send_inst(INTERNAL_OSC);
	lcd_send_inst(FOLLOWER_CONTROL);
	lcd_send_inst(POWER_CONTROL);
	lcd_send_inst(CONTRAST_SET);
	lcd_send_inst(FUNCTION_SET_3);
	lcd_send_inst(DISPLAY_ON);
	backlight_set_white();
}

/**
 @brief sets the display position where the data should be printed.
 @param position what line on the display that should be used.
 return void
 */
void lcd_set_position(uint8_t position){
	lcd_send_inst(LCD_HOME_L1 + position);
}

/**
 @brief lcd_clear, clear the display.
 @param void
 @return void
 */
void lcd_clear(void){
	lcd_send_inst(0x01);
}

/**
 @brief lcd_setROM, sets the display ROM.
 @param void
 @return void
 */
void lcd_setROM(void){
	lcd_send_inst(FUNCTION_SET_1);
	lcd_send_inst(0x72);
	lcd_send_data(ROMB);
	lcd_send_inst(0x38);
}

/**
 @brief lcd_write_string, send a buffer of chars to be printed by function lcd_send_data.
 @param string, a pointer to the string buffer.
 @return void
 */
void lcd_write_string(uint8_t* string){
	do
	{
		lcd_send_data(*string++);
	}
	while(*string);
}
