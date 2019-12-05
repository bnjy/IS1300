/**
 * @file backlight.h
 * @author Benjamin Roth
 * @date Nov 27, 2019
 * @brief header file to backlight.c
 */

#ifndef INC_BACKLIGHT_H_
#define INC_BACKLIGHT_H_
#include <stdint.h>

void backlight_set_white(void);
void backlight_set_red(void);
void backlight_set_green(void);
void backlight_set_brightnes(void);

#endif /* INC_BACKLIGHT_H_ */
