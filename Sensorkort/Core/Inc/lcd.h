/*
 * lcd.h
 *
 *  Created on: Nov 27, 2019
 *      Author: benjamin
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include <stdio.h>
#include <stdlib.h>

#define FUNCTION_SET_1 0x3A
#define EXTENDED_FUNCTION_SET 0x09
#define ENTRY_MODE_SET 0x06
#define BIAS_SETTING 0x1E
#define FUNCTION_SET_2 0x39
#define INTERNAL_OSC 0x1B
#define FOLLOWER_CONTROL 0x6E
#define POWER_CONTROL 0x56
#define CONTRAST_SET 0x7A
#define FUNCTION_SET_3 0x38
#define DISPLAY_ON 0x0F
#define ROMA 0x00
#define ROMB 0x04
#define ROMC 0x0C
#define LCD_HOME_L1	0x80
#define LINE1 0
#define LINE2 LINE1+0x20
#define LINE3 LINE1+0x40
#define	LINE4 LINE1+0x60

void lcd_send_inst(uint8_t inst);
void lcd_send_data(uint8_t data);
void lcd_initialize(void);
void lcd_set_position(uint8_t position);
void lcd_clear(void);
void lcd_setROM(void);
void lcd_write_string(uint8_t* string);


#endif /* INC_LCD_H_ */
