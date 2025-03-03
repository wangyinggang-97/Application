/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
static void Run(void); 
static void ErrorHandler(void);
static void Assert_Failed(void);

/* Public variables-----------------------------------------------------------*/
System_t System = 
{
	Run,
	ErrorHandler,
	Assert_Failed
};

/* Private function prototypes------------------------------------------------*/

/*
	* @name   Run
	* @brief  ϵͳ����
	* @param  None
	* @retval None      
*/
static void Run()
{
	//��ȡ����������
	if(Touch.Scan() == TRUE)
	{
		Touch.Touch_Flag = TRUE;
	}
	if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)== GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		while(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)== GPIO_PIN_RESET)
		{
			  break;
		}
	  SPI_Flash.EraseTotal();
		user_main_printf("EraseTotal is ok!!");
	}
	//GUI����
	 lv_task_handler();
  
}
/*
	* @name   Error_Handler
	* @brief  ϵͳ������
	* @param  None
	* @retval None      
*/
static void ErrorHandler()
{
	/* User can add his own implementation to report the HAL error return state */
}

/*
	* @name   Assert_Failed
	* @brief  ��������������
	* @param  None
	* @retval None      
*/
static void Assert_Failed()
{
	/* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
/********************************************************
  End Of File
********************************************************/
