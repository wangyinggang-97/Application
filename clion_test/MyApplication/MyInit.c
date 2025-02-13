/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
static void Peripheral_Set(void); 

/* Public variables-----------------------------------------------------------*/
MyInit_t MyInit = 
{
	Peripheral_Set
};

/* Private function prototypes------------------------------------------------*/      


/*
	* @name   Peripheral_Set
	* @brief  外设设置
	* @param  None
	* @retval None      
*/
static void Peripheral_Set()
{
	printf("----FreeRTOS操作系统----\r\n");
	printf("----任务管理实验----\r\n\r\n");

	printf("按键功能如下：\r\n");
	printf("KEY1：删除LED2任务\r\n");
	printf("KEY2：重建LED2任务\r\n");
	printf("KEY3：挂起LED3任务\r\n");
	printf("KEY4：恢复LED3任务\r\n\r\n");
	
    HAL_TIM_Base_Start_IT(&htim3); //启动定时器3
}

/********************************************************
  End Of File
********************************************************/
