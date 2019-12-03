/**
  ******************************************************************************
  * File Name          : RTC.c
  * Description        : This file provides code for the configuration
  *                      of the RTC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */
#include "lcd.h"
#include "usart.h"
#include "communication.h"
#include <string.h>
#include "test_com.h"

static char hhmmss[6];
uint8_t *ascii_array;
uint8_t time[8];

/**
 @brief set_time, ask the user for input to set the RTC. The input is placed in buffer @param hhmmss.
 Calls the function char_converter to convert the chars to ASCII. Time is then set with RTC_TimeTypeDef struct
 variables.
 @param void
 */
void set_time(void){
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;

	//Message to print to user
	uint8_t setMsg[] = "Set time HH:MM:SS\n\r";

	//Print message via UART
	HAL_UART_Transmit(&huart5, (uint8_t *)setMsg, strlen(setMsg), 10000);

	//Get HH MM SS from user
	HAL_UART_Receive(&huart5, (uint8_t *)hhmmss, 6, 10000);

	ascii_array = char_converter(hhmmss);

	sTime.Hours = ascii_array[0];
	sTime.Minutes = ascii_array[1];
	sTime.Seconds = ascii_array[2];

	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

uint8_t * char_converter(uint8_t array[]){
	static uint8_t new[3];
	for(int i = 0; i < 3; i++){
		new[i] = (((array[i*2] - 0x30) * 10) + (array[i*2+1] - 0x30));
	}
	return new;
}

/**
 @brief get_time, gets the current time value with function HAL_RTC_GetTime.  Stores the time values on
 char buffer and prints it to the lcd.
 @param void
 */
void get_time(void){
	RTC_TimeTypeDef gTime;
	RTC_DateTypeDef gDate;

	//Get the RTC current time and date
	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);

	sprintf((char *)time, "%02d:%02d:%02d", gTime.Hours, gTime.Minutes, gTime.Seconds);

	lcd_set_position(LINE1);
	lcd_write_string(time);

}

/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /** Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_POS1;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
    
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date 
  */
  sTime.Hours = 0;
  sTime.Minutes = 0;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 1;
  sDate.Year = 0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable Calibration 
  */
  if (HAL_RTCEx_SetCalibrationOutPut(&hrtc, RTC_CALIBOUTPUT_1HZ) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */
    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**RTC GPIO Configuration    
    PB2     ------> RTC_OUT_CALIB 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF0_RTC_50Hz;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
  
    /**RTC GPIO Configuration    
    PB2     ------> RTC_OUT_CALIB 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2);

  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
