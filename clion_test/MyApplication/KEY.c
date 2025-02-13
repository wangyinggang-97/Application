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
	* @brief  获取按键编码
	* @param  None
	* @retval None      
*/
static void GetKeyCode(void)
{
	KeyCode_t KeyCode = KEYNULL;
	
	//检测KEY1
	if(KeyCode == KEYNULL)
	{
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == GPIO_PIN_RESET)
		{
			KeyCode = KEY1;
			//等待KEY1释放
			while(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == GPIO_PIN_RESET)
			{
				osDelay(20); //必须用阻塞延时
			}
		}
	}
	//检测KEY2
	if(KeyCode == KEYNULL)
	{
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_RESET)
		{
			KeyCode = KEY2;
			//等待KEY2释放
			while(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_RESET)
			{
				osDelay(20); //必须用阻塞延时
			}
		}
	}
	//检测KEY3
	if(KeyCode == KEYNULL)
	{
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == GPIO_PIN_RESET)
		{
			KeyCode = KEY3;
			//等待KEY3释放
			while(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == GPIO_PIN_RESET)
			{
				osDelay(20); //必须用阻塞延时
			}
		}
	}
	//检测KEY4
	if(KeyCode == KEYNULL)
	{
		if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin) == GPIO_PIN_RESET)
		{
			KeyCode = KEY4;
			//等待KEY1释放
			while(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin) == GPIO_PIN_RESET)
			{
				osDelay(20); //必须用阻塞延时
			}
		}
	}
	//更新按键编码值
	KEY.KeyCode = KeyCode;
}
/********************************************************
  End Of File
********************************************************/
