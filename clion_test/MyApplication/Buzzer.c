/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
static void Buzzer_ON(void); 
static void Buzzer_OFF(void); 

/* Public variables-----------------------------------------------------------*/
Buzzer_t Buzzer = 
{
	Buzzer_Status_OFF,
	
	Buzzer_ON,
	Buzzer_OFF
};

/* Private function prototypes------------------------------------------------*/      

/*
	* @name   Buzzer_ON
	* @brief  ´ò¿ª·äÃùÆ÷
	* @param  None
	* @retval None      
*/
static void Buzzer_ON(void)
{
	Buzzer.Status = Buzzer_Status_ON;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
}

/*
	* @name   Buzzer_OFF
	* @brief  ¹Ø±Õ·äÃùÆ÷
	* @param  None
	* @retval None      
*/
static void Buzzer_OFF(void)
{
	Buzzer.Status = Buzzer_Status_OFF;
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
}
/********************************************************
  End Of File
********************************************************/
