/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

/* Private function prototypes------------------------------------------------*/      
static void Timer6_Start_IT(void);  //��ʱ��6���ж�ģʽ����
	
/* Public variables-----------------------------------------------------------*/
Timer6_t  Timer6 = 
{
	0,
	0,
	0,
	
	Timer6_Start_IT     
};

/*
	* @name   Timer6_Start_IT
	* @brief  ��ʱ��6���ж�ģʽ����
	* @param  None
	* @retval None      
*/
static void Timer6_Start_IT(void)
{
	HAL_TIM_Base_Start_IT(&htim6); //������ʱ��6
}
/********************************************************
  End Of File
********************************************************/
