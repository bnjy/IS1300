/**
 * @file test_lcd.c
 * @author Benjamin Roth
 * @date Nov 27, 2019
 * @brief a test program to test functions for EADOGS104-A
 */

#include "test_lcd.h"
#include "gpio.h"
#include "lcd.h"
#include "adc.h"

/**
 @brief test_program_lcd, runs all the program lcd test functions.
 @param void
 @return void
 */
void test_program_lcd(void){
	test_lcd_clear();
	test_lcd_initialize();
	test_lcd_setROM();
	lcd_clear();
	test_backlight_set_white();
	test_write_char();
	HAL_Delay(1800);
	lcd_clear();
	test_write_string();
	HAL_Delay(1800);
	lcd_clear();
	test_lcd_set_position();
	lcd_clear();
	test_set_backlight();
}
/**
 @brief test_set_backlight, a test function that turns white and green display color off, and turns on the red
 color to be able to set the backlight strength via PWM. Function backlight_set_brightnes() is called in
 a while loop, to be able to test the PWM on the microcontroller. backlight_set_brightnes enables the
 backlight strength to be to be modified via timer PWM.
 @param void
 @return void
 */
void test_set_backlight(void){
	int i = 0;
	HAL_GPIO_WritePin(GPIOC, Disp_White_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, Disp_Green_Pin, GPIO_PIN_RESET);

	lcd_write_string("Try PWM");

	while(i < 1000000){
		backlight_set_brightnes();
		i++;
	}
}

/**
 @brief test_backlight_set_white, a test function to turn on the white backlight on the display. Calls
 function backlight_set_white. Test is seen as successful if display has white backlight.
 @param void
 @return void
 */
void test_backlight_set_white(void){
	backlight_set_white();
}

/**
 @brief test_write_string, a test function that send a string to lcd_write_string function
 and the string should be printed on the display.
 Test is seen as successful if string appear on display and "test_write_string succeed" is printed via
 serial communication.
 @param void
 @return void
 */
void test_write_string(void){
	lcd_write_string("Wassup");
	uint8_t* test_write_string = "test_write_string succeed\n\r";
	transmit(test_write_string);
}

/**
@brief test_write_char, a test to write a stream of hardcoded instructions of chars to the display.
Test is seen as successful if chars appear on display and "test_write_char succeed" is printed via
serial communication.
@param void
@return void
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
	uint8_t* test_write_char = "test_write_char succeed\n\r";
	transmit(test_write_char);
}

/**
 @brief test_display_initialize, a test to initialize the display.
 Test is seen as successful if "test_lcd_initialize succeed" is printed via
 serial communication.
 @param void
 @return void
 */
void test_lcd_initialize(void){
	lcd_initialize();
	uint8_t* test_lcd_initialize = "test_lcd_initialize succeed\n\r";
	transmit(test_lcd_initialize);
}

/**
 @brief test_lcd_rom, test to set the LCD ROM with function call to lcd_setROM.
 Test is seen as successful if "test_lcd_setROM succeed" is printed via
 serial communication.
 @param void
 @return void
 */
void test_lcd_setROM(void){
	lcd_setROM();
	uint8_t* test_lcd_rom = "test_lcd_setROM succeed\n\r";
	transmit(test_lcd_rom);
}

/**
 @brief test_lcd_clear, a test function to run lcd_clear.
 Test is seen as successful if the display is cleared with information and "test_lcd_clear succeed"
 is printed via serial communication.
 @param void
 @return void
 */
void test_lcd_clear(void){
	lcd_clear();
	uint8_t* test_lcd_clear = "test_lcd_clear succeed\n\r";
	transmit(test_lcd_clear);
}

/**
 @brief test_lcd_set_position, prints string "Line x", where x is the number of the line
 it is going to be printed on. Test is seen as successful if the display show 4 lines with text and
 "test_lcd_clear succeed" is printed via serial communication.
 @param void
 @return void
 */
void test_lcd_set_position(void){
	lcd_set_position(LINE1);
	lcd_write_string("Line 1");
	HAL_Delay(1000);
	lcd_set_position(LINE2);
	lcd_write_string("Line 2");
	HAL_Delay(1000);
	lcd_set_position(LINE3);
	lcd_write_string("Line 3");
	HAL_Delay(1000);
	lcd_set_position(LINE4);
	lcd_write_string("Line 4");
	HAL_Delay(5000);
	uint8_t* test_lcd_set_position = "test_lcd_set_position succeed\n\r";
	transmit(test_lcd_set_position);
}



