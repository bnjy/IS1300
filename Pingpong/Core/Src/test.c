/*
 * test.c
 *
 *  Created on: Nov 1, 2019
 *      Author: Benjamin Roth
 *      Brief:	Test functions for program Pingpong.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "Test.h"
#include "usart.h"
#include "gpio.h"
#include "Pingpong.h"

/**
@brief Test_program, runs all the program test functions.
@param void
 */
void Test_program(void){
	Test_Led();
	Test_blink();
	Test_show_points();
	Test_buttons();
}

/**
@brief Test_buttons, checks if the buttons are working fine.
@param void
 */
void Test_buttons(void){
	int8_t j;

	/* Checking buttons */
	j=4;
	Led_on(j); //Light on

	while(j<9 && j>0){
		if(L_hit() == true){ 	//Wait for left button hit
			j++;				//Next led to the right
			Led_on(j);			//Light on
			HAL_Delay(100);		//100 ms
			while(L_hit() == true); //Wait for button release
			HAL_Delay(100);		//100 ms
		}
		if(R_hit() == true){	//Wait for right button hit
			j--;				//next led to the left
			Led_on(j);			//Led on
			HAL_Delay(100);		//100 ms
			while(R_hit() == true);	//Wait for button release
			HAL_Delay(100);		//100 ms
			if(j<1) j=0;		//start again from left
		}
	}
}

/**
@brief Test_Led, checks if the LED:s are working fine.
@param void
 */
void Test_Led(void){
	int8_t Lednr;
	/* Loop checking that all leds can be turned on */
	for (Lednr = 1; Lednr <= 8; Lednr++){
		Led_on(Lednr);
		HAL_Delay(500);
	}
	Led_on(9);	//Turn off Led8
	HAL_Delay(1000);	//1000 ms
	return;
}

/**
@brief Test_blink, blinks LEDs three times.
@param void
 */
void Test_blink(void){
	int8_t i;
	for(i = 0; i < 4; i++){
		Blink_LEDs();
	}
}

/**
@brief Test_show_points, checks if the LED:s are able to show all possible scores.
@param void
 */
void Test_show_points(void){
	int8_t i;
	int8_t j;
	for(i = 0; i <= 4; i++){
		for(j = 0; j <= 4; j++){
			Show_points(i,j);
		}
	}
}

