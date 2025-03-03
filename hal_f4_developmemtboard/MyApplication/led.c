/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"
/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
static    void LED_ON(uint8_t);   //��
static 	  void LED_OFF(uint8_t);   //�ر�
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
	* @brief  ��aLED
	* @param  Num -> ���
	* @retval None      
*/
static void LED_ON(uint8_t LED_Num)
{
	//����ѡ�����
	switch(LED_Num)
	{
		case LED0:HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_RESET); break;
		case LED1:HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET); break;
		default:System.Assert_Failed();
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
		case LED0:HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET); break;
		case LED1:HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET); break;
		default:System.Assert_Failed();
	}
}
/*
	* @name   LED_Flip
	* @brief  ��תLED
	* @param  Num -> ���
	* @retval None      
*/
static void LED_Flip(uint8_t LED_Num)
{
	//����ѡ�����
	switch(LED_Num)
	{
		case LED0:HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin); break;
		case LED1:HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin); break;
		default:System.Assert_Failed();
	}
}
