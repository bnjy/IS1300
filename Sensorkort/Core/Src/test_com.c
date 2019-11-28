/*
 * test_com.c
 *
 *  Created on: Nov 28, 2019
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
#include "string.h"
#include "communication.h"

void test_program_uart(void){
	lcd_initialize();
	test_recieve();
//	test_transmit();
}

/**
 @brief test_print_to_lcd_from_computer, takes 3 chars from pc and prints it on the display.
 @param void
 @return void
 */
void test_transmit(void){
	uint8_t * string = "test uart transmit";
	transmit(string);
}

void test_recieve(void){
	uint8_t* p = recieve();
	lcd_set_position(LINE1);
	lcd_write_string(p);

}
