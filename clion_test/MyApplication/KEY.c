/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
static void GetKeyCode(void);

/* Public variables-----------------------------------------------------------*/
KEY_t KEY = 
{
	KEYNULL,
	
	GetKeyCode
};

/* Private function prototypes------------------------------------------------*/      

/*
	* @name   GetKeyCode
	* @brief  ��ȡ��������
	* @param  None
	* @retval None      
*/
static void GetKeyCode(void)
{
	KeyCode_t KeyCode = KEYNULL;
	
	//���KEY1
	if(KeyCode == KEYNULL)
	{
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == GPIO_PIN_RESET)
		{
			KeyCode = KEY1;
			//�ȴ�KEY1�ͷ�
			while(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == GPIO_PIN_RESET)
			{
				osDelay(20); //������������ʱ
			}
		}
	}
	//���KEY2
	if(KeyCode == KEYNULL)
	{
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_RESET)
		{
			KeyCode = KEY2;
			//�ȴ�KEY2�ͷ�
			while(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_RESET)
			{
				osDelay(20); //������������ʱ
			}
		}
	}
	//���KEY3
	if(KeyCode == KEYNULL)
	{
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == GPIO_PIN_RESET)
		{
			KeyCode = KEY3;
			//�ȴ�KEY3�ͷ�
			while(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == GPIO_PIN_RESET)
			{
				osDelay(20); //������������ʱ
			}
		}
	}
	//���KEY4
	if(KeyCode == KEYNULL)
	{
		if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin) == GPIO_PIN_RESET)
		{
			KeyCode = KEY4;
			//�ȴ�KEY1�ͷ�
			while(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin) == GPIO_PIN_RESET)
			{
				osDelay(20); //������������ʱ
			}
		}
	}
	//���°�������ֵ
	KEY.KeyCode = KeyCode;
}
/********************************************************
  End Of File
********************************************************/
