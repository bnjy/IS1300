/*
 * pingpong.c
 *
 *  Created on: Nov 1, 2019
 *      Author: Benjamin Roth
 *      Brief:	Pingpong statemachine for Pingpong program
 */

#include <stdio.h>
#include <stdlib.h>
#include "Pingpong.h"

/* Define states for state machine */

typedef enum{
	Start,
	MoveRight,
	MoveLeft,
	ShowScore
} states;

static states State, NextState;

/**
@brief Pingpong, game logic and game states of Pingpong

@param void

@return void, no return value
**/
void Pingpong(void){
	bool ButtonPressed; // To remember that button is pressed
	bool R_turn, L_turn;
	uint32_t Varv, Speed; // Ball speed
	uint8_t Led, R_score, L_score; // LED nr
	State= Start; // Initiate State to Start
	NextState = Start;
	ButtonPressed = false;
	R_turn = true;	//initial bool for right to serve
	L_turn = true;	//initial bool for right to serve
	Speed = 500000; // Number of loops
	R_score = 0;	//initial score right
	L_score = 0;	//initial score left

	/* Infinite loop */
	while (1){
		State = NextState;
		switch (State){ // State machine
		case Start:{
			Led_on(0); // Turn off all LEDs
			if ( L_hit() == true && L_turn == true){ // L serve
				L_turn = false; //if left serve, left cant serve next time
				R_turn = true;	//right turn next time
				Led = 1;
				NextState= MoveRight;
				while ( L_hit() == true ); // wait until button is released
			} else if ( R_hit() == true && R_turn == true ){ // R serve
				R_turn = false;	//if right serve, right cant serve next time
				L_turn = true;	//left turn next time
				Led = 8;
				NextState= MoveLeft;
				while ( R_hit() == true ); // wait until button is released
			}
			else
				NextState = Start; // Stay in Start state
		}
			break;
		case MoveRight:{
			Led_on(Led);
			Varv = Speed;
			while( Varv != 0 ){
				if ( R_hit() ) ButtonPressed = true; // R hit
				Varv--;
			}
			if ( ButtonPressed ){ // R pressed
				if ( Led == 8 ){ // and LED8 active
					NextState = MoveLeft; // return ball
					Speed -= 50000;
					Led=7;
				}
				else{
					L_score++;
					Speed = 500000;
					NextState = ShowScore; // hit to early
				}
			}
			else{
				if ( Led == 9 ){ // no hit or to late
					L_score++;
					Speed = 500000;
					NextState = ShowScore;
				}
				else
					NextState = MoveRight; // ball continues to move right
			}
			if ( !ButtonPressed ) Led++; // prepare to turn next LED on
			ButtonPressed=false;
		}
		break;
		case MoveLeft:{
			Led_on(Led);
			Varv = Speed;
			while(Varv != 0){
				if ( L_hit() ) ButtonPressed = true; // L hit
				Varv--;
			}
			if ( ButtonPressed ){ // L pressed
				if ( Led == 1 ){ // and LED1 active
					NextState=MoveRight; // return ball
					Speed -= 50000;
					Led=2;
				}
				else{
					R_score++;
					Speed = 500000;
					NextState = ShowScore; // hit to early
				}
			}
			else{
				if ( Led == 0 ){ // no hit or to late
					R_score++;
					Speed = 500000;
					NextState = ShowScore;
				}
				else
					NextState = MoveLeft; // ball continues to move left
			}
			if ( !ButtonPressed ) Led--; // prepare to turn next LED on
			ButtonPressed=false;
		}
		break;
		case ShowScore:{
			if(L_score < 4 && R_score < 4){				//keep on playing until someone reach 4 points
			Show_points(L_score, R_score);				//show score
			NextState = Start;							//return to start state
			} else if(L_score == 4 || R_score == 4){ 	//one of the players won the game
				Show_points(L_score, R_score);			//show the final result
				L_score = 0;							//reset left score
				R_score = 0;							//reset right score
				R_turn = true;							//reset right turn to serve
				L_turn = true;							//reset left turn to serve
				NextState = Start;						//return to start state
			}
		}
		break;
		default:
			break;
		}
	}
 } // End of function Pingpong
