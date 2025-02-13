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
	* @brief  ��������
	* @param  None
	* @retval None      
*/
static void Peripheral_Set()
{
	printf("----FreeRTOS����ϵͳ----\r\n");
	printf("----�������ʵ��----\r\n\r\n");

	printf("�����������£�\r\n");
	printf("KEY1��ɾ��LED2����\r\n");
	printf("KEY2���ؽ�LED2����\r\n");
	printf("KEY3������LED3����\r\n");
	printf("KEY4���ָ�LED3����\r\n\r\n");
	
    HAL_TIM_Base_Start_IT(&htim3); //������ʱ��3
}

/********************************************************
  End Of File
********************************************************/
