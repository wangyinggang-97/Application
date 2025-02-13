/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
static void LED_ON(uint8_t); 
static void LED_OFF(uint8_t);
static void LED_Flip(uint8_t);

/* Public variables-----------------------------------------------------------*/
LED_t LED = 
{
	LED_ON,
	LED_OFF,
	LED_Flip
};

/* Private function prototypes------------------------------------------------*/      

/*
	* @name   LED_ON
	* @brief  ��LED
	* @param  Num -> ���
	* @retval None      
*/
static void LED_ON(uint8_t LED_Num)
{
	//����ѡ�����
	switch(LED_Num)
	{
		case LED1: HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET); break;
		case LED2: HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET); break;
		case LED3: HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET); break;
		default: System.Assert_Failed();
	}
}

/*
	* @name   LED_OFF
	* @brief  �ر�LED
	* @param  Num -> ���
	* @retval None      
*/
static void LED_OFF(uint8_t LED_Num)
{
	//����ѡ�����
	switch(LED_Num)
	{
		case LED1: HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET); break;
		case LED2: HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET); break;
		case LED3: HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET); break;
		default: System.Assert_Failed();
	}
}

/*
	* @name   LED_Flip
	* @brief  ȡ��LED
	* @param  Num -> ���
	* @retval None      
*/
static void LED_Flip(uint8_t LED_Num)
{
	//����ѡ�����
	switch(LED_Num)
	{
		case LED1: HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin); break;
		case LED2: HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin); break;
		case LED3: HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin); break;
		default: System.Assert_Failed();
	}
}
/********************************************************
  End Of File
********************************************************/
