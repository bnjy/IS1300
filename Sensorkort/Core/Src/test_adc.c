/**
 * @file test_adc.c
 * @author Benjamin Roth
 * @date Nov 27, 2019
 * @brief a test program to test functions for read the adc value.
 */

#include "test_adc.h"

char adc_str[10];

/**
 @brief test_program_adc, runs all the program adc test functions.
 @param void
 @return void
 */
void test_program_adc(void){
	test_get_adc_value();
}

/**
 @brief test_get_adc_value, calls function get_adc_value that starts adc and read the analog signal and returns
 a int with the value. The value is then printed on the display. Test is seen as successful if the value
 and "test_write_string succeed" is printed via serial communication.
 @param void
 @return void
 */
void test_get_adc_value(void){
	lcd_initialize();
	lcd_clear();
	lcd_set_position(LINE1);
	uint32_t value = get_adc_value();
	sprintf((char *)adc_str, "%d" , value);
	lcd_write_string("ADC value");
	lcd_set_position(LINE2);
	lcd_write_string(adc_str);
	HAL_Delay(3000);
	uint8_t* test_get_adc_value = "test_get_adc_value succeed\n\r";
	transmit(test_get_adc_value);
}
