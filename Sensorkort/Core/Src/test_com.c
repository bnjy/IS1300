/*
 * test_com.c
 *
 *  Created on: Nov 28, 2019
 *      Author: benjamin
 */

#include "test_com.h"
#include "lcd.h"
#include "rtc.h"

void test_program_uart(void){
	lcd_initialize();
	lcd_clear();
	test_set_time();
	test_get_time();
//	test_recieve();
//	test_transmit();
}

/**
 @brief test_get_current_time, calls function set_time in rtc.c and sets the time from user input.
 @param void
 @return void
 */
void test_set_time(void){
	set_time();
}

/**
 @brief test_print_current_time, calls function get_time in rtc.c and prints the current time in the RTC module.
 @param void
 @return void
 */
void test_get_time(void){
	get_time();
}


/**
 @brief test_transmit, prints string "test uart transmit" to uart serial device.
 @param void
 @return void
 */
void test_transmit(void){
	uint8_t * string = "test uart transmit";
	transmit(string);
}

/**
 @brief test_recieve, tests uart recieve() function.
 @param void
 @return void
 */
void test_recieve(void){
	uint8_t* p;
	p = recieve();
	lcd_set_position(LINE1);
	lcd_write_string(p);

}
