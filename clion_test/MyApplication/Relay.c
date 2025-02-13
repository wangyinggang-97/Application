/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
static void Relay_ON(void); 
static void Relay_OFF(void);
static void Relay_Flip(void);

/* Public variables-----------------------------------------------------------*/
Relay_t Relay = 
{
	Relay_Status_OFF,
	
	Relay_ON,
	Relay_OFF,
	Relay_Flip
};

/* Private function prototypes------------------------------------------------*/      

/*
	* @name   Relay_ON
	* @brief  打开继电器
	* @param  None
	* @retval None      
*/
static void Relay_ON(void)
{
	Relay.Status = Relay_Status_ON;
	HAL_GPIO_WritePin(Relay_GPIO_Port,Relay_Pin,GPIO_PIN_SET);
}

/*
	* @name   Relay_OFF
	* @brief  关闭继电器
	* @param  None
	* @retval None      
*/
static void Relay_OFF(void)
{
	Relay.Status = Relay_Status_OFF;
	HAL_GPIO_WritePin(Relay_GPIO_Port,Relay_Pin,GPIO_PIN_RESET);
}

/*
	* @name   Relay_Flip
	* @brief  取反继电器
	* @param  None
	* @retval None      
*/
static void Relay_Flip(void)
{
	if(Relay.Status == Relay_Status_ON)
		Relay.Status = Relay_Status_OFF;
	else
		Relay.Status = Relay_Status_ON;
	
	HAL_GPIO_TogglePin(Relay_GPIO_Port,Relay_Pin);
}
/********************************************************
  End Of File
********************************************************/
