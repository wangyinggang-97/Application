/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
static void Timer6_Start_IT(void);   //?????6???ж???????
static void Delay_us(uint16_t nus);   //???????????

/* Public variables-----------------------------------------------------------*/
Timer6_t  Timer6 =
{
    0,
    0,

    Timer6_Start_IT,
    Delay_us
};

/* Private function prototypes------------------------------------------------*/
static void Delay_us(uint16_t nus)   //???????????
{
    __HAL_TIM_SET_COUNTER(&htim6, 0);  // set the counter value a 0
    __HAL_TIM_ENABLE(&htim6);          // start the counter
    // wait for the counter to reach the us input in the parameter
    while (__HAL_TIM_GET_COUNTER(&htim6) < nus);
    __HAL_TIM_DISABLE(&htim6);         // stop the counter

}

/*
	* @name   Peripheral_Set
	* @brief  ????????
	* @param  None
	* @retval None
*/
static void Timer6_Start_IT()
{

    HAL_TIM_Base_Start_IT(&htim6); //?????????6
}

/********************************************************
  End Of File
********************************************************/
