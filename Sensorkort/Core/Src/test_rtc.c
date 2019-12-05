/**
 * @file test_rtc.c
 * @author Benjamin Roth
 * @date Nov 27, 2019
 * @brief a test program to test functions for RTC
 */

#include "test_rtc.h"


/**
 @brief test_program_rtc, runs all the program rtc test functions.
 @param void
 @return void
 */
void test_program_rtc(void){
	lcd_clear();
	test_set_time();
	test_get_time();
}

/**
 @brief test_set_time, calls function set_time() that asks the user for a input to set the RTC.
 @param void
 @return void
 */
void test_set_time(void){
	set_time();
}

/**
 @brief test_get_time, calls function get_time() that displays the time on the display for 10 seconds.
 @param void
 @return void
 */
void test_get_time(void){
	int i = 0;
	while(i < 2000){
		get_time();
		i++;
	}
}
