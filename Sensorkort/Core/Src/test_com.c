/**
 * @file test_com.c
 * @author Benjamin Roth
 * @date Nov 27, 2019
 * @brief a test program to test functions for USB communication.
 */

#include "test_com.h"
#include "lcd.h"
#include "rtc.h"

/**
 @brief test_program_communication, runs all the program communication test functions.
 @param void
 @return void
 */
void test_program_communication(void){
	test_transmit_recieve();
}

/**
 @brief test_transmit_recieve, tests uart recieve() and transmit() functions. Function prints a message
 to user via serial communication, to make the user print 10 chars. The 10 chars that the user types is
 recieved and shown (lcd_write_string) on the display. Test is seen as successful if string
 "test_transmit_recieve succeed" is printed via serial communication.
 @param void
 @return void
 */
void test_transmit_recieve(void){
	uint8_t * string = "type 10 chars to the display\n\r";
	transmit(string);

	uint8_t* p;
	p = recieve();
	lcd_clear();
	lcd_set_position(LINE1);
	lcd_write_string(p);
	HAL_Delay(3000);

	uint8_t * test = "test_transmit_recieve succeed\n\r";
	transmit(test);

}
