/*
*********************************************************************************************************
*
*	模块名称 : LED指示灯驱动模块
*	文件名称 : bsp_led.c
*	版    本 : V1.0
*	说    明 : 驱动LED指示灯
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2018-09-05 armfly  正式发布
*
*	Copyright (C), 2015-2030, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#include "MyApplication.h"

static    void LED_ON(uint8_t);   //打开
static 	  void LED_OFF(uint8_t);   //关闭
static 	  void LED_Flip(uint8_t);
/* Public variables-----------------------------------------------------------*/
LED_t LED={
	LED_ON,
	LED_OFF,
	LED_Flip
};
/* Private function prototypes------------------------------------------------*/      
/*
	* @name   LED_ON
	* @brief  打开aLED
	* @param  Num -> 编号
	* @retval None      
*/
static void LED_ON(uint8_t LED_Num)
{
	//条件选择语句
	switch(LED_Num)
	{
		case LED0:HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_RESET); break;
		case LED1:HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET); break;
		//default:System.Assert_Failed();
	}
}
/*
	* @name   LED_OFF
	* @brief  关闭LED
	* @param  Num -> 编号
	* @retval None      
*/
static void LED_OFF(uint8_t LED_Num)
{
	//条件选择语句
	switch(LED_Num)
	{
		case LED0:HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET); break;
		case LED1:HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET); break;
		//default:System.Assert_Failed();
	}
}
/*
	* @name   LED_Flip
	* @brief  反转LED
	* @param  Num -> 编号
	* @retval None      
*/
static void LED_Flip(uint8_t LED_Num)
{
	//条件选择语句
	switch(LED_Num)
	{
		case LED0:HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin); break;
		case LED1:HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin); break;
		//default:System.Assert_Failed();
	}
}


/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
