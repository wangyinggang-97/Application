/**
  ************************************* Copyright ****************************** 
  *
  *                 (C) Copyright 2025,--,China, GCU.
  *                            All Rights Reserved  
  * FileName   : Servo.c   
  * Version    : v1.0		
  * Author     : --			
  * Date       : 2025-03-05         
  * Description:    
  * Function List:  
  	1. ....
  	   <version>: 		
  <modify staff>:
  		  <data>:
   <description>:  
  	2. ...
  ******************************************************************************
 */
 
/*include----------------------------------------------------------------------*/
#include "MyApplication.h"
/*define-----------------------------------------------------------------------*/


/*variate----------------------------------------------------------------------*/


/*statement--------------------------------------------------------------------*/


/*Function prototype Begin*****************************************************/
/***********************************************************
*@fuction	:Servo_Init
*@brief		:
*@param		:--
*@return	:void
*@author	:wygssd
*@date		:2025-03-05
***********************************************************/

void Servo_Init(void)
{
		  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
}

/***********************************************************
*@fuction	:Servo_SetAngle
*@brief		:
*@param		:--
*@return	:void
*@author	:wygssd
*@date		:2025-03-05
***********************************************************/

void Servo_SetAngle(uint8_t angle) {
    if (angle > 180) angle = 180;  // 限制角度范围
    uint16_t pulse = 500 + (angle * 2000 / 180);  // 计算占空比（0.5ms - 2.5ms）
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse);
}

/***********************************************************
*@fuction	:Servo_Test
*@brief		:
*@param		:--
*@return	:void
*@author	:wygssd
*@date		:2025-03-05
***********************************************************/

void Servo_Test(void)
{
  	Servo_SetAngle(0);   // 转到 0°
		HAL_Delay(1000);

		Servo_SetAngle(90);  // 转到 90°
		HAL_Delay(1000);

		Servo_SetAngle(180); // 转到 180°
		HAL_Delay(1000);
}
/*Function prototype End*******************************************************/


/**
 **************************************************************
 
--*/


